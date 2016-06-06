#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

int main() {
    const int TILE_SIZE = 32;
    const int WORLD_WIDTH = 10;
    const int WORLD_HEIGHT = 18;
    const int BLOCK_SIZE = 7;
    const std::array<sf::Color, BLOCK_SIZE> colors {
        sf::Color(0x0, 0xff, 0xff),
        sf::Color(0x80, 0x0, 0xff),
        sf::Color(0xff, 0x0, 0xff),
        sf::Color(0xc0, 0xc0, 0xc0),
        sf::Color(0x80,0xff, 0x0),
        sf::Color(0xff, 0xff, 0x0),
        sf::Color(0xff, 0x0, 0x0)
    };
    std::array<sf::Sprite, BLOCK_SIZE> sprites{};

    int flags = sf::Style::Titlebar | sf::Style::Close;
    sf::VideoMode videoMode(WORLD_WIDTH * TILE_SIZE, WORLD_HEIGHT * TILE_SIZE);
    sf::RenderWindow window(videoMode, "Blocks", flags);

    sf::Texture block;
    if (block.loadFromFile("assets/block.png")) {
        std::cout << "Couldn't load \"assets/block.png\"" << std::endl;
    }
    for (std::size_t i = 0; i < sprites.size(); ++i) {
        sprites[i].setTexture(block);
        sprites[i].setColor(colors.at(i));
    }

    sf::Event event;
    bool running = true;
    while (running) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        window.clear();
        for (int i = 0; i < WORLD_WIDTH; ++i) {
            for (int j = 0; j < WORLD_HEIGHT; ++j) {
                int index = j * WORLD_WIDTH + i;
                sprites[index % sprites.size()].setPosition(i * 32, j * 32);
                window.draw(sprites[index % sprites.size()]);
            }
        }
        window.display();
    }
    return 0;
}
