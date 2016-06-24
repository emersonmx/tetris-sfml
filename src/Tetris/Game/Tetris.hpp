#ifndef TETRIS_GAME_TETRIS_HPP_
#define TETRIS_GAME_TETRIS_HPP_

#include "Tetris/Defs.hpp"
#include "Tetris/Game/Tetromino.hpp"

namespace tetris {

class Tetris {
    public:
        class Listener {
            public:
                virtual ~Listener() {}

                virtual void gameStarted(Tetris* tetris) {}
                virtual void gameOver(Tetris* tetris) {}

                virtual void tetrominoUpdated(const Tetromino& tetromino) {}
                virtual void tetrominoFixed(const Tetromino& tetromino) {}
                virtual void linesErased(int start, int end) {}
        };

        enum class InputDirection {
            LEFT=-1, NONE, RIGHT
        };

        static const int WORLD_WIDTH{10};
        static const int WORLD_HEIGHT{18};

        InputDirection inputMovement() { return inputMovement_; }
        void setInputMovement(const InputDirection movement) {
            inputMovement_ = movement;
        }
        InputDirection inputRotation() { return inputRotation_; }
        void setInputRotation(const InputDirection rotation) {
            inputRotation_= rotation;
        }
        bool fastFall() { return fastFall_; }
        void setFastFall(const bool fastFall) { fastFall_= fastFall; }

        void create();
        void destroy();

        void update(const float deltaTime);

    private:
        using BlockDataArray = std::array<Tetromino::RotationIntArray,
              static_cast<int>(Tetromino::Type::SIZE)>;

        static constexpr const float DEFAULT_DELAY{0.8f};
        static constexpr const float FAST_FALL_DELAY{0.05f};

        void moveTetromino();
        void rotateTetromino();
        void moveDownTetromino();
        void eraseLines();

        void restoreCurrentTetromino();
        void saveCurrentTetromino();

        bool hasCollisions();
        void nextTetromino();
        void setupBlockDataArray();

        BlockDataArray blockDataArray_{};
        Matrix<bool, WORLD_WIDTH, WORLD_HEIGHT> worldBlocks_{};
        Tetromino currentTetromino_{};
        Tetromino currentTetrominoCopy_{};

        InputDirection inputMovement_{InputDirection::NONE};
        InputDirection inputRotation_{InputDirection::NONE};
        bool fastFall_{false};
        float timer_{0.0f};
        float delay_{DEFAULT_DELAY};

        bool gameOver_{false};
};

} /* namespace tetris */
#endif /* TETRIS_GAME_TETRIS_HPP_ */
