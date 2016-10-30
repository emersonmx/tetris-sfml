#include "Tetris/GameObjects/Tetromino.hpp"

#include "Tetris/App.hpp"

namespace tetris {
namespace gameobjects {

void Tetromino::create(const sf::Texture& blockTexture) {
    blockSprites_.resize(tetris::game::Tetromino::BLOCK_SIZE);

    for (auto& block : blockSprites_) {
        block.setTexture(blockTexture);
    }
}

void Tetromino::updateTetromino(const tetris::game::Tetromino& tetromino) {
    auto blocks = tetromino.getBlocks();
    for (int i = 0; i < tetris::game::Tetromino::BLOCK_SIZE; ++i) {
        auto& block = blocks[i];
        int type = static_cast<int>(tetromino.getType());

        blockSprites_[i].setPosition(
            block.x * App::TILE_SIZE,
            block.y * App::TILE_SIZE
        );
        blockSprites_[i].setColor(colors_[type]);
    }
}

} /* namespace gameobjects */
} /* namespace tetris */
