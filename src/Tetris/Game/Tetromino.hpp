#ifndef TETRIS_GAME_TETROMINO_HPP_
#define TETRIS_GAME_TETROMINO_HPP_

#include <array>

namespace tetris {
namespace game {

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

        Position getPosition() const { return position_; }
        void setPosition(const Position& position) { position_ = position; }
        Position getPivot() const { return pivot_; }
        void setPivot(const Position& pivot) { pivot_ = pivot; }
        Type getType() const { return type_; }
        void setType(const Type type) { type_ = type; }
        BlockArray getBlocks() const;

        void loadRotationsFromIntArray(const RotationIntArray& blocks);

        void move(const Position& position);
        void rotateLeft();
        void rotateRight();

    private:
        using BlockIntArray = std::array<int, BLOCK_SIZE>;

        BlockArray loadBlockFromIntArray(const BlockIntArray& blocks);

        Position position_{};
        Position pivot_{1, 2};
        Type type_;

        int rotation_{0};
        RotationArray rotationArray_{};
};

} /* namespace game */
} /* namespace tetris */
#endif /* TETRIS_GAME_TETROMINO_HPP_ */
