#ifndef TETRIS_GAME_TETROMINO_HPP_
#define TETRIS_GAME_TETROMINO_HPP_

#include <array>
#include <vector>

namespace tetris {

class Tetromino {
    public:
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

        using Block = Position;
        using Pivot = Position;
        using BlockArray = std::array<Block, 4>;
        using RotationArray = std::array<BlockArray, 4>;

        Tetromino() = default;
        Tetromino(const RotationArray& rotationArray, const Position& position,
                  const Type& type, const Pivot& pivot = {1, 2});

        Position position() const { return position_; }
        void setPosition(const Position& position) { position_ = position; }
        Pivot pivot() const { return pivot_; }
        void setPivot(const Pivot& pivot) { pivot_ = pivot; }
        Type type() const { return type_; }
        void setType(const Type type) { type_ = type; }
        int rotation() const { return rotation_; }
        void setRotation(const int rotation) { rotation_ = rotation; }
        void setRotationArray(const RotationArray& rotationArray) {
            rotationArray_ = rotationArray;
        }
        bool fastFall() const { return fastFall_; }
        void setFastFall(const bool fastFall) { fastFall_ = fastFall; }

        BlockArray getBlocks();
        BlockArray getComputedBlocks();

        void move(const Position& position);
        void turnLeft();
        void turnRight();

    private:
        Position position_{};
        Pivot pivot_{1, 2};
        Type type_;

        int rotation_{0};
        RotationArray rotationArray_{};
        bool fastFall_{false};
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETROMINO_HPP_ */
