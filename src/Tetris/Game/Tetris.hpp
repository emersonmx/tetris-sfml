#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include <unordered_map>

#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

class Tetris {
    public:
        static const int WORLD_WIDTH = 10;
        static const int WORLD_HEIGHT = 18;

        Tetromino& currentTetromino() { return currentTetromino_; }
        Tetromino nextTetromino() const;

        void create();
        void destroy();

        void update();

    private:
        void setupTetrominoHash();

        std::array<bool, WORLD_WIDTH * WORLD_HEIGHT> world_;
        std::unordered_map<Tetromino::Type, Tetromino> tetrominoHash_;

        Tetromino currentTetromino_;
        Tetromino::Type nextTetromino_;
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
