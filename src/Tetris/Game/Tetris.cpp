#include "Tetris/Game/Tetris.hpp"

namespace tetris {

void Tetris::create() {
    setupBlockDataArray();
    nextTetromino();
}

void Tetris::destroy() {
    blockDataArray_ = {};
    worldBlocks_ = {};
    currentTetromino_ = {};
    currentTetrominoCopy_ = {};

    inputMovement_ = InputDirection::NONE;
    inputRotation_ = InputDirection::NONE;
    fastFall_ = false;
    timer_ = 0.0f;
    delay_ = DEFAULT_DELAY;

    gameOver_ = false;
}

void Tetris::update(const float deltaTime) {
    timer_ += deltaTime;

    delay_ = fastFall_ ? FAST_FALL_DELAY : DEFAULT_DELAY;

    saveCurrentTetromino();
    moveTetromino();
    rotateTetromino();
    moveDownTetromino();

    inputMovement_ = inputRotation_ = InputDirection::NONE;
    delay_ = DEFAULT_DELAY;
}

void Tetris::moveTetromino() {
    int movement = static_cast<int>(inputMovement_);
    currentTetromino_.move({movement, 0});
    if (hasCollisions()) {
        restoreCurrentTetromino();
    }
}

void Tetris::rotateTetromino() {
    if (inputMovement_ == InputDirection::LEFT) {
        currentTetromino_.rotateLeft();
    } else if (inputMovement_ == InputDirection::RIGHT) {
        currentTetromino_.rotateRight();
    }
    if (hasCollisions()) {
        restoreCurrentTetromino();
    }
}

void Tetris::moveDownTetromino() {
    if (timer_ >= delay_) {
        saveCurrentTetromino();

        Tetromino::Position fallMovement{0, 1};
        currentTetromino_.move(fallMovement);

        if (hasCollisions()) {
            for (auto block : currentTetrominoCopy_.blocks()) {
                worldBlocks_[block.x][block.y] = true;
            }
            nextTetromino();
        }
        timer_ = 0.0f;
    }
}

void Tetris::eraseLines() {
    int k = WORLD_HEIGHT - 1;
    for (int i = WORLD_HEIGHT - 1; i > 0; --i) {
        int count = 0;
        for (int j = 0; j < WORLD_WIDTH; ++j) {
            if (worldBlocks_[i][j]) {
                count++;
            }
            worldBlocks_[k][j] = worldBlocks_[i][j];
        }
        if (count < WORLD_WIDTH) {
            k--;
        }
    }
}

void Tetris::restoreCurrentTetromino() {
    currentTetromino_ = currentTetrominoCopy_;
}

void Tetris::saveCurrentTetromino() {
    currentTetrominoCopy_ = currentTetromino_;
}

bool Tetris::hasCollisions() {
    for (auto block : currentTetromino_.blocks()) {
        if (block.x < 0 || block.x >= WORLD_WIDTH) {
            return true;
        }
        if (block.y < 0 || block.y >= WORLD_HEIGHT) {
            return true;
        }
        if (worldBlocks_[block.x][block.y]) {
            return true;
        }
    }

    return false;
}

void Tetris::nextTetromino() {
    int index = rand() % static_cast<int>(Tetromino::Type::SIZE);
    Tetromino tetromino;
    tetromino.loadRotationsFromIntArray(blockDataArray_[index]);
    tetromino.move({4, 1});

    currentTetromino_ = tetromino;
}

void Tetris::setupBlockDataArray() {
    blockDataArray_ = {{
        {{
            4,5,6,7,
            2,6,10,14,
            8,9,10,11,
            1,5,9,13
        }},
        {{
            4,8,9,10,
            5,6,9,13,
            8,9,10,14,
            5,9,12,13
        }},
        {{
            6,8,9,10,
            5,9,13,14,
            8,9,10,12,
            4,5,9,13
        }},
        {{
            5,6,9,10,
            5,6,9,10,
            5,6,9,10,
            5,6,9,10
        }},
        {{
            5,6,8,9,
            5,9,10,14,
            9,10,12,13,
            4,8,9,13
        }},
        {{
            5,8,9,10,
            5,9,10,13,
            8,9,10,13,
            5,8,9,13
        }},
        {{
            8,9,13,14,
            6,9,10,13,
            8,9,13,14,
            5,8,9,12
        }}
    }};
}

} /* namespace tetris */
