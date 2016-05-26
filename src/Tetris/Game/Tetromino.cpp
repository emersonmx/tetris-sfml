#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

Tetromino::Tetromino(const Tetromino::RotationArray& rotationArray, Tetromino::Type type)
    : type_(type), rotationArray_{rotationArray} {}

void Tetromino::turnLeft() {
    rotation_--;
    rotation_ = rotation_ < 0 ? (ROTATION_SIZE - 1) : rotation_;
}

void Tetromino::turnRight() {
    rotation_++;
    rotation_ = rotation_ % ROTATION_SIZE;
}

void Tetromino::resetRotation() {
    rotation_ = 0;
}

Tetromino::BlockArray Tetromino::getBlocks() {
    return std::move(rotationArray_[rotation_]);
}

Tetromino::BlockArray Tetromino::getComputedBlocks() {
    BlockArray blocks{rotationArray_[rotation_]};
    for (auto& block : blocks) {
        block.x -= pivot_x;
        block.y -= pivot_y;
    }
    return std::move(rotationArray_[rotation_]);
}

} /* namespace tetris */
