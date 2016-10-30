#ifndef TETRIS_GAMEOBJECTS_GAMEAREA_HPP_
#define TETRIS_GAMEOBJECTS_GAMEAREA_HPP_

#include "Tetris/GameObjects/BlockRenderer.hpp"
#include "Tetris/Game/Tetris.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {
namespace gameobjects {

class GameArea : public BlockRenderer {
    public:
        void create(const sf::Texture& blockTexture);
        void updateWorld(const tetris::game::Tetris::WorldBlockArray& blocks);
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_GAMEAREA_HPP_ */
