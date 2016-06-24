#include "Tetris/Game/Tetromino.hpp"

#include <cmath>
#include <algorithm>

namespace tetris {

void Tetromino::loadRotationsFromIntArray(const RotationIntArray& blocks) {
    const int directionSize = static_cast<int>(Direction::SIZE);

    std::array<int, directionSize> intArray;
    for (int i = 0; i < directionSize; ++i) {
        auto begin = blocks.begin() + (i * directionSize);
        std::copy_n(begin, directionSize, intArray.begin());
        rotationArray_[i] = loadBlockFromIntArray(intArray);
    }
}

Tetromino::BlockArray Tetromino::blocks() {
    BlockArray blocks{rotationArray_[rotation_]};
    for (auto& block : blocks) {
        block.x = position_.x + block.x - pivot_.x;
        block.y = position_.y + block.y - pivot_.y;
    }
    return std::move(blocks);
}

void Tetromino::move(const Position& position) {
    position_.x += position.x;
    position_.y += position.y;
}

void Tetromino::rotateLeft() {
    rotation_--;
    rotation_ = rotation_ < 0 ? (static_cast<int>(Direction::SIZE) - 1) : rotation_;
}

void Tetromino::rotateRight() {
    rotation_++;
    rotation_ = rotation_ % static_cast<int>(Direction::SIZE);
}

Tetromino::BlockArray Tetromino::loadBlockFromIntArray(
        const BlockIntArray& blocks) {
    const int blockSize = static_cast<int>(blocks.size());
    Tetromino::BlockArray result{};

    for (int i = 0; i < blockSize; ++i) {
        int block = blocks.at(i);
        int x = block % blockSize;
        int y = static_cast<int>(block / blockSize);
        result[i] = { x, y };
    }

    return result;
}

} /* namespace tetris */
