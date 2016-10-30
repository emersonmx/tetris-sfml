#include "Tetris/GameObjects/GameArea.hpp"

#include "Tetris/App.hpp"

using namespace tetris::game;

namespace tetris {
namespace gameobjects {

void GameArea::create(const sf::Texture& blockTexture) {
    blockSprites_.resize(Tetris::WORLD_WIDTH * Tetris::WORLD_HEIGHT);

    for (auto& block : blockSprites_) {
        block.setTexture(blockTexture);
    }
}

void GameArea::updateWorld(const Tetris::WorldBlockArray& blocks) {
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

} /* namespace gameobjects */
} /* namespace tetris */
