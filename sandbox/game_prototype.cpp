#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

#include "MXG/Application.hpp"
#include "Tetris/Game/Tetromino.hpp"

class Game : public mxg::Application {
    public:
        int WORLD_WIDTH{10};
        int WORLD_HEIGHT{18};
        int TILE_SIZE{32};
        unsigned int WINDOW_WIDTH{
            static_cast<unsigned int>(WORLD_WIDTH * TILE_SIZE)
        };
        unsigned int WINDOW_HEIGHT{
            static_cast<unsigned int>(WORLD_HEIGHT * TILE_SIZE)
        };
        unsigned int FRAMES_PER_SECOND{60};
        float TIME_STEP{static_cast<float>(1.0f / FRAMES_PER_SECOND)};
        enum class Texture : int {
            BLOCK, SIZE
        };
        enum class Sprite : int {
            CURRENT_TETROMINO, SIZE
        };

    protected:
        void create() override {
            createWindow();
            loadAssets();
            setupWorld();
            setupObjects();
        }

        void createWindow() {
            sf::VideoMode mode{WINDOW_WIDTH, WINDOW_HEIGHT};
            sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
            std::string title = "Tetris prototype";
            window_.create(mode, title, style);
        }

        void loadAssets() {
            loadTexture("assets/block.png", Texture::BLOCK);
        }

        void setupObjects() {
            sf::Texture& block = textures_.at(static_cast<int>(Texture::BLOCK));

            sf::Sprite tetromino{block};
            sprites_[static_cast<int>(Sprite::CURRENT_TETROMINO)] = tetromino;
        }

        void tick() override {
            sf::Time time = clock_.restart();

            processEvents();
            timeAccumulator_ += time.asSeconds();
            if (timeAccumulator_ >= TIME_STEP) {
                update();
                timeAccumulator_ -= TIME_STEP;
            }
            render();
        }

        void processEvents() {
            sf::Event event;
            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    exit();
                } else if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Down:
                            currentTetromino_.setFastFall(true);
                            break;
                        default:
                            break;
                    }
                } else if (event.type == sf::Event::KeyReleased) {
                    switch (event.key.code) {
                        case sf::Keyboard::Left:
                            currentTetromino_.move({-1, 0});
                            break;
                        case sf::Keyboard::Right:
                            currentTetromino_.move({1, 0});
                            break;
                        case sf::Keyboard::Down:
                            currentTetromino_.setFastFall(false);
                            break;
                        case sf::Keyboard::Z:
                            currentTetromino_.turnLeft();
                            break;
                        case sf::Keyboard::X:
                            currentTetromino_.turnRight();
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        void update() {
            dropDelay_ += TIME_STEP;
            if (dropDelay_ >= 1) {
                dropDelay_ = 0;
                currentTetromino_.move({0, 1});
            }
        }

        void render() {
            window_.clear(sf::Color{42, 42, 42});
            tetris::Tetromino::BlockArray blocks = currentTetromino_.getComputedBlocks();
            tetris::Tetromino::Position position = currentTetromino_.position();
            sf::Sprite& spr = sprites_[static_cast<int>(Sprite::CURRENT_TETROMINO)];
            for (auto& block : blocks) {
                spr.setPosition(sf::Vector2f(
                    block.x * TILE_SIZE,
                    block.y * TILE_SIZE
                ));
                window_.draw(spr);
            }
            window_.display();
        }

        void setupWorld() {
            tetris::Tetromino tetrominoI{{
                tetris::Tetromino::BlockArray {{
                    {0, 1}, {1, 1}, {2, 1}, {3, 1}
                }},
                tetris::Tetromino::BlockArray {{
                    {2, 0}, {2, 1}, {2, 2}, {2, 3}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {2, 2}, {3, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 0}, {1, 1}, {1, 2}, {1, 3}
                }},
            }, {4, 1}, tetris::Tetromino::Type::I};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::I)] = tetrominoI;

            tetris::Tetromino tetrominoJ{{
                tetris::Tetromino::BlockArray {{
                    {0, 1}, {0, 2}, {1, 2}, {2, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 3}, {1, 2}, {1, 1}, {2, 1}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {2, 2}, {2, 3}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 3}, {1, 3}, {1, 2}, {1, 1}
                }},
            }, {4, 1}, tetris::Tetromino::Type::J};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::J)] = tetrominoJ;

            tetris::Tetromino tetrominoL{{
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {2, 2}, {2, 1}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {1, 2}, {1, 3}, {2, 3}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 3}, {0, 2}, {1, 2}, {2, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 1}, {1, 1}, {1, 2}, {1, 3}
                }},
            }, {4, 1}, tetris::Tetromino::Type::L};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::L)] = tetrominoL;

            tetris::Tetromino tetrominoO{{
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {2, 1}, {2, 2}, {1, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {2, 1}, {2, 2}, {1, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {2, 1}, {2, 2}, {1, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {2, 1}, {2, 2}, {1, 2}
                }},
            }, {4, 1}, tetris::Tetromino::Type::O};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::O)] = tetrominoO;

            tetris::Tetromino tetrominoS{{
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {1, 1}, {2, 1}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {1, 2}, {2, 2}, {2, 3}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 3}, {1, 3}, {1, 2}, {2, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 1}, {0, 2}, {1, 2}, {1, 3}
                }},
            }, {4, 1}, tetris::Tetromino::Type::S};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::S)] = tetrominoS;

            tetris::Tetromino tetrominoT{{
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {2, 2}, {1, 1}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {1, 2}, {1, 3}, {2, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {2, 2}, {1, 3}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 1}, {1, 2}, {1, 3}, {0, 2}
                }},
            }, {4, 1}, tetris::Tetromino::Type::T};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::T)] = tetrominoT;

            tetris::Tetromino tetrominoZ{{
                tetris::Tetromino::BlockArray {{
                    {0, 1}, {1, 1}, {1, 2}, {2, 2}
                }},
                tetris::Tetromino::BlockArray {{
                    {1, 3}, {1, 2}, {2, 2}, {2, 1}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 2}, {1, 2}, {1, 3}, {2, 3}
                }},
                tetris::Tetromino::BlockArray {{
                    {0, 3}, {0, 2}, {1, 2}, {1, 1}
                }},
            }, {4, 1}, tetris::Tetromino::Type::Z};
            tetrominoes_[static_cast<int>(tetris::Tetromino::Type::Z)] = tetrominoZ;

            currentTetromino_ = tetrominoZ;
        }

    private:
        void loadTexture(const std::string& filename, const Texture name) {
            sf::Texture texture;
            if (!texture.loadFromFile(filename)) {
                std::cout << "Texture \"" << filename << "\" couldn't be loaded." << std::endl;
                return;
            }

            textures_[static_cast<int>(name)] = texture;
        }

        sf::RenderWindow window_;
        sf::Clock clock_;
        std::array<sf::Texture, static_cast<std::size_t>(Texture::SIZE)> textures_;
        std::array<sf::Sprite, static_cast<std::size_t>(Sprite::SIZE)> sprites_;

        std::array<tetris::Tetromino, static_cast<std::size_t>(tetris::Tetromino::Type::SIZE)> tetrominoes_;
        tetris::Tetromino currentTetromino_;

        float timeAccumulator_{0.0f};
        float dropDelay_{0.0f};
};

int main() {
    Game game;
    return game.run();
}
