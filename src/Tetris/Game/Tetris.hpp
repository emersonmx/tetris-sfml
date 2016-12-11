#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include <random>
#include <functional>

#include "Tetris/Defs.hpp"
#include "Tetris/Game/Tetromino.hpp"

namespace tetris {
namespace game {

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
        int getScore() const { return score_; }
        void setScore(const int score);
        void addScore(const int value);
        int getHighScore() const { return highScore_; }
        void setHighScore(const int highScore);

        void create();
        void create(int seed);
        void destroy();

        void update(const float deltaTime);

        std::function<void(Tetris&)> gameStartedCallback;
        std::function<void(Tetris&)> gameOverCallback;
        std::function<void(const int)> scoreUpdatedCallback;
        std::function<void(const int)> highScoreUpdatedCallback;
        std::function<void(void)> linesErasedCallback;
        std::function<void(const Tetromino&)> tetrominoUpdatedCallback;
        std::function<void(const Tetromino&)> nextTetrominoCallback;
        std::function<void(const WorldBlockArray&)> worldUpdatedCallback;

    private:
        using BlockDataArray = std::array<Tetromino::RotationIntArray,
              static_cast<int>(Tetromino::Type::SIZE)>;

        constexpr static const float DEFAULT_DELAY{0.8f};
        constexpr static const float FAST_FALL_DELAY{0.05f};
        constexpr static const int SCORE_POINT{1};
        constexpr static const int SCORE_BASE_POINTS{300};
        constexpr static const char* SCOREBOARD_FILE = ".scoreboard";

        void loadHighScore();
        void saveHighScore();

        Tetromino newTetromino();
        void resetCurrentTetromino(const Tetromino& tetromino);
        void checkGameOver();

        void moveTetromino();
        void rotateTetromino();
        void moveDownTetromino();
        void eraseLines();

        void restoreCurrentTetromino();
        void saveCurrentTetromino();

        bool hasCollisions();
        void setupBlockDataArray();

        void fireGameStarted();
        void fireGameOver();
        void fireScoreUpdated();
        void fireHighScoreUpdated();
        void fireLinesErased();
        void fireTetrominoUpdated();
        void fireNextTetrominoUpdated();
        void fireWorldUpdated();

        BlockDataArray blockDataArray_{};
        WorldBlockArray worldBlockArray_{};
        Tetromino currentTetromino_{};
        Tetromino currentTetrominoCopy_{};
        Tetromino nextTetromino_{};

        InputDirection inputMovement_{InputDirection::NONE};
        InputDirection inputRotation_{InputDirection::NONE};
        bool fastFall_{false};
        float timer_{0.0f};
        float delay_{DEFAULT_DELAY};

        bool gameOver_{false};
        int score_{0};
        int highScore_{0};

        std::mt19937 rng_;
};

} /* namespace game */
} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
