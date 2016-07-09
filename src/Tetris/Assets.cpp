#include "Tetris/Assets.hpp"

#include <iostream>

namespace tetris {

void Assets::loadAssets() {
    block_ = loadTextureFromFile("assets/block.png");
    background_ = loadTextureFromFile("assets/background.png");
}

sf::Texture Assets::loadTextureFromFile(const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cout << "Couldn't load \"" << filename << "\"\n";
    }

    return texture;
}

} /* namespace tetris */
