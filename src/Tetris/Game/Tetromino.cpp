#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

Tetromino::Tetromino(const Tetromino::RotationArray& rotationArray,
        const Tetromino::Position& position,
        const Tetromino::Type& type, const Tetromino::Pivot& pivot)
    : position_{position}, pivot_{pivot}, type_{type},
      rotationArray_{rotationArray} {}

Tetromino::BlockArray Tetromino::getBlocks() {
    return std::move(rotationArray_[rotation_]);
}

Tetromino::BlockArray Tetromino::getComputedBlocks() {
    BlockArray blocks{rotationArray_[rotation_]};
    for (auto& block : blocks) {
        block.x -= pivot_.x;
        block.y -= pivot_.y;
    }
    return std::move(rotationArray_[rotation_]);
}

void Tetromino::turnLeft() {
    rotation_--;
    rotation_ = rotation_ < 0 ? (ROTATION_SIZE - 1) : rotation_;
}

void Tetromino::turnRight() {
    rotation_++;
    rotation_ = rotation_ % ROTATION_SIZE;
}

void Tetromino::fall() {
    position_.y++;
}

} /* namespace tetris */
