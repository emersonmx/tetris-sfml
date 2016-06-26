#include "Tetris/BlockRenderer.hpp"

#include <iostream>

#include "Tetris/Application.hpp"

namespace tetris {

void BlockRenderer::create(Assets& assets) {
    sf::Texture& blockTexture = assets.block();

    colors_ = {
        sf::Color::Cyan,
        sf::Color(128, 0, 128),
        sf::Color::Magenta,
        sf::Color(128, 128, 128),
        sf::Color::Green,
        sf::Color::Yellow,
        sf::Color::Red
    };

    for (auto& block : currentTetromino_) {
        block.setTexture(blockTexture);
    }

    for (auto& block : blockSprites_) {
        block.setTexture(blockTexture);
    }
}

void BlockRenderer::destroy() {
}

void BlockRenderer::gameStarted(Tetris& tetris) {
}

void BlockRenderer::gameOver(Tetris& tetris) {
}

void BlockRenderer::scoreUpdated(const int score) {
}

void BlockRenderer::tetrominoUpdated(const Tetromino& tetromino) {
    auto blocks = tetromino.blocks();
    for (int i = 0; i < Tetromino::BLOCK_SIZE; ++i) {
        auto& block = blocks[i];
        int type = static_cast<int>(tetromino.type());

        currentTetromino_[i].setPosition(
            block.x * Application::TILE_SIZE,
            block.y * Application::TILE_SIZE
        );
        currentTetromino_[i].setColor(colors_[type]);
    }
}

void BlockRenderer::worldUpdated(const Tetris::WorldBlockArray& worldBlockArray) {
    for (int i = 0; i < Tetris::WORLD_HEIGHT; ++i) {
        for (int j = 0; j < Tetris::WORLD_WIDTH; ++j) {
            int value = worldBlockArray[i][j];
            int type = value - 1;
            int x = j * Application::TILE_SIZE;
            int y = i * Application::TILE_SIZE;
            auto& blockSprite = blockSprites_[i * Tetris::WORLD_WIDTH + j];
            blockSprite.setPosition(x, y);
            blockSprite.setColor(colors_[type]);
            blockSprite.setActive(value > 0);
        }
    }
}

void BlockRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= transformable_.getTransform();

    for (auto& block : currentTetromino_) {
        if (block.active()) {
            target.draw(block, states);
        }
    }

    for (auto& block : blockSprites_) {
        if (block.active()) {
            target.draw(block, states);
        }
    }
}

} /* namespace tetris */
