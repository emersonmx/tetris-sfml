#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include <unordered_map>

#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

class Tetris {
    public:
        static const int WORLD_WIDTH = 10;
        static const int WORLD_HEIGHT = 18;

        Tetromino& currentTetromino();
        Tetromino nextTetromino() const;

        void create();
        void destroy();

        void update();

    private:
        std::array<Tetromino::Block, WORLD_WIDTH * WORLD_HEIGHT> world_;
        std::unordered_map<Tetromino::Type, Tetromino> tetrominoHash_;

        Tetromino::Type currentTetromino_;
        Tetromino::Type nextTetromino_;
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
