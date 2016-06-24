#include <ctime>

#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "Tetris/Game/Tetromino.hpp"

// Consts
constexpr const int WORLD_WIDTH{10};
constexpr const int WORLD_HEIGHT{18};
constexpr const int TILE_SIZE{32};
constexpr const int WINDOW_WIDTH{WORLD_WIDTH * TILE_SIZE};
constexpr const int WINDOW_HEIGHT{WORLD_HEIGHT * TILE_SIZE};
constexpr const int FRAMES_PER_SECOND{60};

using WorldBlockArray = std::array<bool, WORLD_WIDTH * WORLD_HEIGHT>;
using BlockDataArray = std::array<tetris::Tetromino::RotationIntArray, 7>;

bool hasCollisions(const tetris::Tetromino::BlockArray& blocks, const WorldBlockArray& world);
tetris::Tetromino nextTetromino(const BlockDataArray& blockData);

int main() {
    srand(time(0));

    // Window
    sf::VideoMode mode(WINDOW_WIDTH, WINDOW_HEIGHT);
    std::string windowTitle = "Tetris";
    sf::Uint32 flags = sf::Style::Titlebar | sf::Style::Close;
    sf::RenderWindow window(mode, windowTitle, flags);
    window.setFramerateLimit(FRAMES_PER_SECOND);

    // Assets
    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block.png");
    sf::Sprite blockSprite(blockTexture);

    sf::Clock clock;
    float timer = 0.0f, delay = 0.8f;
    int inputRotation = 0;
    int inputMovement = 0;
    WorldBlockArray world{0};

    BlockDataArray blockData{{
        {{
            4,5,6,7,
            2,6,10,14,
            8,9,10,11,
            1,5,9,13
        }},
        {{
            4,8,9,10,
            5,6,9,13,
            8,9,10,14,
            5,9,12,13
        }},
        {{
            6,8,9,10,
            5,9,13,14,
            8,9,10,12,
            4,5,9,13
        }},
        {{
            5,6,9,10,
            5,6,9,10,
            5,6,9,10,
            5,6,9,10
        }},
        {{
            5,6,8,9,
            5,9,10,14,
            9,10,12,13,
            4,8,9,13
        }},
        {{
            5,8,9,10,
            5,9,10,13,
            8,9,10,13,
            5,8,9,13
        }},
        {{
            8,9,13,14,
            6,9,10,13,
            8,9,13,14,
            5,8,9,12
        }}
    }};

    tetris::Tetromino currentTetromino = nextTetromino(blockData);
    tetris::Tetromino currentTetrominoCopy;

    bool running = true;
    while (running) {
        float delta = clock.restart().asSeconds();
        timer += delta;

        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    inputMovement = -1;
                } else if (event.key.code == sf::Keyboard::Right) {
                    inputMovement = 1;
                }
                if (event.key.code == sf::Keyboard::Z) {
                    inputRotation = -1;
                } else if (event.key.code == sf::Keyboard::X) {
                    inputRotation = 1;
                }
            }
        }

        // Update

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            delay = 0.05f;
        }

        currentTetrominoCopy = currentTetromino;

        currentTetromino.move({inputMovement, 0});
        if (hasCollisions(currentTetromino.blocks(), world)) {
            currentTetromino = currentTetrominoCopy;
        }

        if (inputRotation < 0) {
            currentTetromino.rotateLeft();
        } else if (inputRotation > 0) {
            currentTetromino.rotateRight();
        }
        if (hasCollisions(currentTetromino.blocks(), world)) {
            currentTetromino = currentTetrominoCopy;
        }

        if (timer >= delay) {
            currentTetrominoCopy = currentTetromino;

            tetris::Tetromino::Position fallMovement{0, 1};
            currentTetromino.move(fallMovement);
            tetris::Tetromino::BlockArray previewBlocks = currentTetromino.blocks();

            if (hasCollisions(previewBlocks, world)) {
                for (auto block : currentTetrominoCopy.blocks()) {
                    world[block.y * WORLD_WIDTH + block.x] = true;
                }
                currentTetromino = nextTetromino(blockData);
            }
            timer = 0.0f;
        }

        int k = WORLD_HEIGHT - 1;
        for (int i = WORLD_HEIGHT - 1; i > 0; --i) {
            int count = 0;
            for (int j = 0; j < WORLD_WIDTH; ++j) {
                if (world.at(i * WORLD_WIDTH + j)) {
                    count++;
                }
                world[k * WORLD_WIDTH + j] = world[i * WORLD_WIDTH + j];
            }
            if (count < WORLD_WIDTH) {
                k--;
            }
        }

        inputMovement = inputRotation = 0;
        delay = 0.8f;

        // Draw
        window.clear(sf::Color::White);

        tetris::Tetromino::BlockArray tetrominoBlocks = currentTetromino.blocks();
        for (auto& block : tetrominoBlocks) {
            blockSprite.setPosition(block.x * TILE_SIZE, block.y * TILE_SIZE);
            blockSprite.setColor(sf::Color::Green);
            window.draw(blockSprite);
        }

        for (std::size_t i = 0; i < world.size(); ++i) {
            bool value = world.at(i);
            if (!value) {
                continue;
            }
            int x = (i % WORLD_WIDTH) * TILE_SIZE;
            int y = static_cast<int>(i / WORLD_WIDTH) * TILE_SIZE;
            blockSprite.setPosition(x, y);
            blockSprite.setColor(sf::Color::Red);
            window.draw(blockSprite);
        }

        window.display();
    }
    return 0;
}

bool hasCollisions(const tetris::Tetromino::BlockArray& blocks, const WorldBlockArray& world) {
    for (auto block : blocks) {
        if (block.x < 0 || block.x >= WORLD_WIDTH) {
            return true;
        }
        if (block.y < 0 || block.y >= WORLD_HEIGHT) {
            return true;
        }
        if (world.at(block.y * WORLD_WIDTH + block.x)) {
            return true;
        }
    }
    return false;
}

tetris::Tetromino nextTetromino(const BlockDataArray& blockData) {
    int index = rand() % static_cast<int>(tetris::Tetromino::Type::SIZE);
    tetris::Tetromino tetromino;
    tetromino.loadRotationsFromIntArray(blockData.at(index));
    tetromino.move({4, 1});
    return tetromino;
}
