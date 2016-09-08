#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include <random>
#include <functional>

#include "Tetris/Defs.hpp"
#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

class Tetris {
    public:
        static const int WORLD_WIDTH{10};
        static const int WORLD_HEIGHT{18};

        using WorldBlockArray = Matrix<int, WORLD_HEIGHT, WORLD_WIDTH>;
        enum class InputDirection {
            LEFT=-1, NONE, RIGHT
        };

        InputDirection getInputMovement() { return inputMovement_; }
        void setInputMovement(const InputDirection movement) {
            inputMovement_ = movement;
        }
        InputDirection getInputRotation() { return inputRotation_; }
        void setInputRotation(const InputDirection rotation) {
            inputRotation_= rotation;
        }
        bool getFastFall() { return fastFall_; }
        void setFastFall(const bool fastFall) { fastFall_= fastFall; }
        bool isGameOver() { return gameOver_; }

        void create();
        void create(int seed);
        void destroy();

        void update(const float deltaTime);

        std::function<void(Tetris&)> gameStartedCallback;
        std::function<void(Tetris&)> gameOverCallback;
        std::function<void(const int)> scoreUpdatedCallback;
        std::function<void(const Tetromino&)> tetrominoUpdatedCallback;
        std::function<void(const WorldBlockArray&)> worldUpdatedCallback;

    private:
        using BlockDataArray = std::array<Tetromino::RotationIntArray,
              static_cast<int>(Tetromino::Type::SIZE)>;

        constexpr static const float DEFAULT_DELAY{0.8f};
        constexpr static const float FAST_FALL_DELAY{0.05f};

        void moveTetromino();
        void rotateTetromino();
        void moveDownTetromino();
        void eraseLines();

        void restoreCurrentTetromino();
        void saveCurrentTetromino();

        bool hasCollisions();
        bool collidedInTheBlocks();
        bool collidedWalls();
        bool collidedOnTheGround();
        void nextTetromino();
        void setupBlockDataArray();

        void fireGameStarted();
        void fireGameOver();
        void fireScoreUpdated();
        void fireTetrominoUpdated();
        void fireWorldUpdated();

        BlockDataArray blockDataArray_{};
        WorldBlockArray worldBlockArray_{};
        Tetromino currentTetromino_{};
        Tetromino currentTetrominoCopy_{};

        InputDirection inputMovement_{InputDirection::NONE};
        InputDirection inputRotation_{InputDirection::NONE};
        bool fastFall_{false};
        float timer_{0.0f};
        float delay_{DEFAULT_DELAY};

        bool gameOver_{false};
        int score_{0};

        std::mt19937 rng_;
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
