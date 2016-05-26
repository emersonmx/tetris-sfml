#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

class Tetris {
    public:
        static const int WORLD_WIDTH = 10;
        static const int WORLD_HEIGHT = 18;

        void create();
        void destroy();

        void update();

    private:
        int nextUUID() { return uuid_++; }

        std::array<Tetromino::Block, WORLD_WIDTH * WORLD_HEIGHT> world_;
        int uuid_ = 1;
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
