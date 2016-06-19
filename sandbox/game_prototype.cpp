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
const int BLOCK_SIZE{4};

int main() {
    // Window
    sf::VideoMode mode(WINDOW_WIDTH, WINDOW_HEIGHT);
    std::string windowTitle = "Tetris";
    sf::Uint32 flags = sf::Style::Titlebar | sf::Style::Close;
    sf::RenderWindow window(mode, windowTitle, flags);
    window.setFramerateLimit(FRAMES_PER_SECOND);

    // Assets
    sf::Texture blockTexture;
    blockTexture.loadFromFile("assets/block.png");

    bool running = true;
    while (running) {
        // Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        // Update

        // Draw
        window.clear(sf::Color(16, 16, 16));
        window.display();
    }
    return 0;
}
