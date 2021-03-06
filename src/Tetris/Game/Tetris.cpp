#include "Tetris/Game/Tetris.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdexcept>
#include <algorithm>

namespace tetris {
namespace game {

void Tetris::setScore(const int score) {
    score_ = score;
    fireScoreUpdated();
}

void Tetris::addScore(const int value) {
    setScore(score_ + value);
}

void Tetris::setHighScore(const int highScore) {
    highScore_ = highScore;
    fireHighScoreUpdated();
}

void Tetris::create() {
    create(time(0));
}

void Tetris::create(int seed) {
    rng_.seed(seed);

    loadHighScore();

    setupBlockDataArray();

    resetCurrentTetromino(newTetromino());
    checkGameOver();

    fireGameStarted();
}

void Tetris::destroy() {
    saveHighScore();

    blockDataArray_ = {};
    worldBlockArray_ = {};
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
    if (gameOver_) {
        return;
    }

    timer_ += deltaTime;

    delay_ = fastFall_ ? FAST_FALL_DELAY : DEFAULT_DELAY;

    saveCurrentTetromino();
    moveTetromino();
    rotateTetromino();
    moveDownTetromino();

    inputMovement_ = inputRotation_ = InputDirection::NONE;
    delay_ = DEFAULT_DELAY;

    if (gameOver_) {
        fireGameOver();
    }
}

void Tetris::loadHighScore() {
    std::ifstream scoreboard;
    int highScore;
    scoreboard.open(SCOREBOARD_FILE);
    if (scoreboard.is_open()) {
        scoreboard >> highScore;
        scoreboard.close();
        setHighScore(highScore);
    }
}

void Tetris::saveHighScore() {
    std::ofstream scoreboard;
    scoreboard.open(SCOREBOARD_FILE);
    if (scoreboard.is_open()) {
        scoreboard << getHighScore();
        scoreboard.close();
    } else {
        std::cout << "Unable to save scoreboard" << std::endl;
    }
}

Tetromino Tetris::newTetromino() {
    std::uniform_int_distribution<> uniform_dist(0,
            static_cast<int>(Tetromino::Type::SIZE) - 1);
    int index = uniform_dist(rng_);

    Tetromino tetromino;
    tetromino.setType(static_cast<Tetromino::Type>(index));
    tetromino.loadRotationsFromIntArray(blockDataArray_[index]);
    return tetromino;
}

void Tetris::resetCurrentTetromino(const Tetromino& tetromino) {
    currentTetromino_ = tetromino;
    if (currentTetromino_.getType() == Tetromino::Type::Z) {
        currentTetromino_.move({4, 0});
    } else {
        currentTetromino_.move({4, 1});
    }
    nextTetromino_ = newTetromino();
}

void Tetris::checkGameOver() {
    if (hasCollisions()) {
        gameOver_ = true;
    }
}

void Tetris::moveTetromino() {
    int movement = static_cast<int>(inputMovement_);
    currentTetromino_.move({movement, 0});
    if (hasCollisions()) {
        restoreCurrentTetromino();
    }
}

void Tetris::rotateTetromino() {
    if (inputRotation_ == InputDirection::LEFT) {
        currentTetromino_.rotateLeft();
    } else if (inputRotation_ == InputDirection::RIGHT) {
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
        addScore(SCORE_POINT);

        if (hasCollisions()) {
            for (auto block : currentTetrominoCopy_.getBlocks()) {
                int type = static_cast<int>(currentTetromino_.getType()) + 1;
                worldBlockArray_[block.y][block.x] = type;
            }

            firePlacedTetromino();

            resetCurrentTetromino(nextTetromino_);
            checkGameOver();

            eraseLines();
            fireWorldUpdated();
            fireNextTetrominoUpdated();
        }
        timer_ = 0.0f;
    }

    fireTetrominoUpdated();
}

void Tetris::eraseLines() {
    int k = WORLD_HEIGHT - 1;
    int linesErased = 0;
    for (int i = WORLD_HEIGHT - 1; i > 0; --i) {
        int count = 0;
        for (int j = 0; j < WORLD_WIDTH; ++j) {
            if (worldBlockArray_[i][j] > 0) {
                count++;
            }
            worldBlockArray_[k][j] = worldBlockArray_[i][j];
        }
        if (count < WORLD_WIDTH) {
            k--;
        } else {
            linesErased++;
        }
    }

    if (linesErased > 0) {
        addScore(SCORE_BASE_POINTS * linesErased + (SCORE_BASE_POINTS * (linesErased - 1) / 3));
        fireScoreUpdated();
        fireLinesErased();
    }
}

void Tetris::restoreCurrentTetromino() {
    currentTetromino_ = currentTetrominoCopy_;
}

void Tetris::saveCurrentTetromino() {
    currentTetrominoCopy_ = currentTetromino_;
}

bool Tetris::hasCollisions() {
    for (auto block : currentTetromino_.getBlocks()) {
        if (block.x < 0 || block.x >= WORLD_WIDTH) {
            return true;
        }
        if (block.y < 0 || block.y >= WORLD_HEIGHT) {
            return true;
        }
        if (worldBlockArray_[block.y][block.x] > 0) {
            return true;
        }
    }

    return false;
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

void Tetris::fireGameStarted() {
    if (gameStartedCallback) {
        gameStartedCallback(*this);
    }

    fireScoreUpdated();
    fireTetrominoUpdated();
    fireNextTetrominoUpdated();
    fireWorldUpdated();
}

void Tetris::fireGameOver() {
    if (gameOverCallback) {
        gameOverCallback(*this);
    }
}

void Tetris::fireScoreUpdated() {
    if (scoreUpdatedCallback) {
        scoreUpdatedCallback(score_);
    }

    if (score_ >= highScore_) {
        setHighScore(score_);
    }
}

void Tetris::fireHighScoreUpdated() {
    if (highScoreUpdatedCallback) {
        highScoreUpdatedCallback(highScore_);
    }
}

void Tetris::fireLinesErased() {
    if (linesErasedCallback) {
        linesErasedCallback();
    }
}

void Tetris::firePlacedTetromino() {
    if (placedTetrominoCallback) {
        placedTetrominoCallback();
    }
}

void Tetris::fireTetrominoUpdated() {
    if (tetrominoUpdatedCallback) {
        tetrominoUpdatedCallback(currentTetromino_);
    }
}

void Tetris::fireNextTetrominoUpdated() {
    if (nextTetrominoCallback) {
        nextTetrominoCallback(nextTetromino_);
    }
}

void Tetris::fireWorldUpdated() {
    if (worldUpdatedCallback) {
        worldUpdatedCallback(worldBlockArray_);
    }
}

} /* namespace game */
} /* namespace tetris */
