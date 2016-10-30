#ifndef TETRIS_GAMEOBJECTS_TETROMINO_HPP_
#define TETRIS_GAMEOBJECTS_TETROMINO_HPP_

#include "Tetris/GameObjects/BlockRenderer.hpp"
#include "Tetris/Game/Tetromino.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {
namespace gameobjects {

class Tetromino : public BlockRenderer {
    public:
        void create(const sf::Texture& blockTexture);
        void updateTetromino(const tetris::game::Tetromino& tetromino);
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_TETROMINO_HPP_ */
