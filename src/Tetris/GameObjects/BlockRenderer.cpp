#include "Tetris/GameObjects/BlockRenderer.hpp"

#include "Tetris/App.hpp"

namespace tetris {

void BlockRenderer::create(Assets& assets) {
    sf::Texture& blockTexture = assets.getBlock();

    colors_ = {
        sf::Color(50, 255, 255),
        sf::Color(50, 50, 255),
        sf::Color(255, 123, 50),
        sf::Color(255, 255, 50),
        sf::Color(99, 255, 50),
        sf::Color(99, 50, 99),
        sf::Color(255, 50, 50)
    };

    for (auto& block : currentTetromino_) {
        block.setTexture(blockTexture);
    }

    for (auto& block : blockSprites_) {
        block.setTexture(blockTexture);
    }
}

void BlockRenderer::tetrominoUpdated(const Tetromino& tetromino) {
    auto blocks = tetromino.getBlocks();
    for (int i = 0; i < Tetromino::BLOCK_SIZE; ++i) {
        auto& block = blocks[i];
        int type = static_cast<int>(tetromino.getType());

        currentTetromino_[i].setPosition(
            block.x * App::TILE_SIZE,
            block.y * App::TILE_SIZE
        );
        currentTetromino_[i].setColor(colors_[type]);
    }
}

void BlockRenderer::worldUpdated(const Tetris::WorldBlockArray& blocks) {
    for (int i = 0; i < Tetris::WORLD_HEIGHT; ++i) {
        for (int j = 0; j < Tetris::WORLD_WIDTH; ++j) {
            int value = blocks[i][j];
            int type = value - 1;
            int x = j * App::TILE_SIZE;
            int y = i * App::TILE_SIZE;
            auto& blockSprite = blockSprites_[i * Tetris::WORLD_WIDTH + j];
            blockSprite.setPosition(x, y);
            blockSprite.setColor(colors_[type]);
            blockSprite.setActive(value > 0);
        }
    }
}

void BlockRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (auto& block : currentTetromino_) {
        if (block.getActive()) {
            target.draw(block, states);
        }
    }

    for (auto& block : blockSprites_) {
        if (block.getActive()) {
            target.draw(block, states);
        }
    }
}

} /* namespace tetris */
