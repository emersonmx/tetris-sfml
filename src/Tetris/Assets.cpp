#include "Tetris/Assets.hpp"

#include <iostream>

namespace tetris {

void Assets::loadAssets() {
    block_ = loadTextureFromFile("assets/block.png");
    grid_ = loadTextureFromFile("assets/grid.png");

    defaultFont_ = loadFontFromFile("assets/Chewy.ttf");
}

sf::Texture Assets::loadTextureFromFile(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cout << "Couldn't load \"" << filename << "\"\n";
    }

    return texture;
}

sf::Font Assets::loadFontFromFile(const std::string& filename) {
    sf::Font font;
    if (!font.loadFromFile(filename)) {
        std::cout << "Couldn't load \"" << filename << "\"\n";
    }

    return font;
}

} /* namespace tetris */
