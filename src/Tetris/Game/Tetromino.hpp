#ifndef TETRIS_GAME_TETROMINO_HPP_
#define TETRIS_GAME_TETROMINO_HPP_

#include <array>
#include <vector>

namespace tetris {

class Tetromino {
    public:
        static const int ROTATION_SIZE = 4;

        struct Position {
            int x;
            int y;
        };
        enum class Type {
            I, J, L, O, S, T, Z
        };
        using Block = Position;
        using Pivot = Block;
        using BlockArray = std::array<Block, 4>;
        using RotationArray = std::array<BlockArray, 4>;

        Tetromino(const RotationArray& rotationArray, const Position& position,
                  const Type& type, const Pivot& pivot = {1, 2});

        int x() const { return position_.x; }
        int y() const { return position_.y; }
        Pivot pivot() const { return pivot_; }
        Type type() const { return type_; }

        bool fastFall() const { return fastFall_; }
        void setFastFall(bool fastFall) { fastFall_ = fastFall; }

        BlockArray getBlocks();
        BlockArray getComputedBlocks();

        void moveLeft() { position_.x--; }
        void moveRight() { position_.x++; }
        void turnLeft();
        void turnRight();

        void _fall();

    private:
        Position position_;
        Pivot pivot_;
        Type type_;

        int rotation_ = 0;
        bool fastFall_ = false;
        RotationArray rotationArray_{};
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETROMINO_HPP_ */
