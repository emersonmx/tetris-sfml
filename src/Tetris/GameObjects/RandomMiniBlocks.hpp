#ifndef TETRIS_GAMEOBJECTS_RANDOMMINIBLOCKS_HPP_
#define TETRIS_GAMEOBJECTS_RANDOMMINIBLOCKS_HPP_

#include "Tetris/App.hpp"
#include "Tetris/GameObjects/BlockRenderer.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {
namespace gameobjects {

class RandomMiniBlocks : public BlockRenderer {
    public:
        void create(const sf::Texture& blockTexture);

    private:
        const float HALF_TILE_SIZE = App::TILE_SIZE / 2.0f;
        static const char* BLOCK_POSITIONS;
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_RANDOMMINIBLOCKS_HPP_ */
