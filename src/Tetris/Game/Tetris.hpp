#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include <array>

namespace tetris {

class Tetris {
    public:
        static const int WORLD_WIDTH = 10;
        static const int WORLD_HEIGHT = 18;

        void create();
        void destroy();

        void update();

    private:
        enum class Block {
            EMPTY,
            FILLED
        };

        std::array<Block, WORLD_WIDTH * WORLD_HEIGHT> world_;
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
