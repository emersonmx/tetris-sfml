#ifndef TETRIS_GAME_TETROMINO_HPP_
#define TETRIS_GAME_TETROMINO_HPP_

#include <array>
#include <vector>

namespace tetris {

class Tetromino {
    public:
        static const int ROTATION_SIZE = 4;

        struct Block {
            int x;
            int y;
        };
        enum class Type {
            NONE, I, J, L, O, S, T, Z
        };
        using BlockArray = std::array<Block, 4>;
        using RotationArray = std::array<BlockArray, 4>;

        Tetromino(const RotationArray& rotationArray);

        void turnLeft();
        void turnRight();
        void resetRotation();
        BlockArray getBlocks();
        BlockArray getComputedBlocks();

        int x;
        int y;
        Type type;

        int pivot_x = 1;
        int pivot_y = 2;

    private:
        int rotation_{};
        RotationArray rotationArray_{};
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETROMINO_HPP_ */
