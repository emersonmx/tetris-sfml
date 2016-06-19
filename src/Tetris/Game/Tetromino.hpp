#ifndef TETRIS_GAME_TETROMINO_HPP_
#define TETRIS_GAME_TETROMINO_HPP_

#include <array>
#include <vector>

namespace tetris {

class Tetromino {
    public:
        constexpr static const int BLOCK_SIZE = 4;
        constexpr static const int ROTATION_SIZE = BLOCK_SIZE;

        struct Position {
            int x;
            int y;
        };
        enum class Type {
            I, J, L, O, S, T, Z, SIZE
        };
        enum class Direction {
            UP, RIGHT, DOWN, LEFT, SIZE
        };

        using BlockArray = std::array<Position, BLOCK_SIZE>;
        using RotationIntArray = std::array<int, BLOCK_SIZE * ROTATION_SIZE>;
        using RotationArray = std::array<BlockArray, ROTATION_SIZE>;

        Tetromino() = default;

        Position position() const { return position_; }
        void setPosition(const Position& position) { position_ = position; }
        Position pivot() const { return pivot_; }
        void setPivot(const Position& pivot) { pivot_ = pivot; }
        Type type() const { return type_; }
        void setType(const Type type) { type_ = type; }
        int rotation() const { return rotation_; }
        void setRotation(const int rotation) { rotation_ = rotation; }
        void setRotationArray(const RotationArray& rotationArray) {
            rotationArray_ = rotationArray;
        }
        bool fastFall() const { return fastFall_; }
        void setFastFall(const bool fastFall) { fastFall_ = fastFall; }

        void loadRotationsFromIntArray(const RotationIntArray& blocks);

        BlockArray getBlocks();
        BlockArray getComputedBlocks();

        void move(const Position& position);
        void turnLeft();
        void turnRight();

    private:
        using BlockIntArray = std::array<int, BLOCK_SIZE>;

        BlockArray loadBlockFromIntArray(const BlockIntArray& blocks);

        Position position_{};
        Position pivot_{1, 2};
        Type type_;

        int rotation_{0};
        RotationArray rotationArray_{};
        bool fastFall_{false};
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETROMINO_HPP_ */
