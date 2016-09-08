#include <array>

#include "gtest/gtest.h"

#include "Tetris/Game/Tetris.hpp"

using namespace tetris;

void worldWalk(const Tetris::WorldBlockArray& world,
        const std::function<void(int, int, int)>& func) {
    for (int i = 0; i < Tetris::WORLD_HEIGHT; ++i) {
        for (int j = 0; j < Tetris::WORLD_WIDTH; ++j) {
            func(world[i][j], i, j);
        }
    }
}

void printWorld(const Tetris::WorldBlockArray& world) {
    worldWalk(world, [&](int value, int i, int j) {
        if (value) {
            std::cout << "#";
        } else {
            std::cout << ".";
        }
        if (j == Tetris::WORLD_WIDTH - 1) {
            std::cout << std::endl;
        }
    });
}

void printGame(const Tetris::WorldBlockArray& world, const Tetromino& tetromino) {
    worldWalk(world, [&](int value, int i, int j) {
        bool tetrominoRendered = false;
        auto blocks = tetromino.getBlocks();
        for (auto block : blocks) {
            if (block.x == j && block.y == i) {
                std::cout << "@";
                tetrominoRendered = true;
                break;
            }
        }

        if (!tetrominoRendered) {
            if (value) {
                std::cout << "#";
            } else {
                std::cout << ".";
            } 
        }

        if (j == Tetris::WORLD_WIDTH - 1) {
            std::cout << std::endl;
        }
    });
}

bool checkWorldEmpty(const Tetris::WorldBlockArray& world) {
    bool result = true;
    worldWalk(world, [&](int value, int i, int j) {
        if (value) {
            result = false;
        }
    });
    return result;
}

class TetrisTest : public ::testing::Test {
    public:
        constexpr static const int DEFAULT_DELAY = 1.0f;
        constexpr static const int DEFAULT_SEED = 42;

        TetrisTest() {
        }
        virtual ~TetrisTest() {}

        Tetris tetris;
};

TEST_F(TetrisTest, CreateTetrisObject) {
    bool result = false;

    tetris.gameStartedCallback = [&](Tetris& t) {
        result = !t.getFastFall();
    };
    tetris.create();
    tetris.destroy();

    ASSERT_TRUE(result);
}

TEST_F(TetrisTest, TetrisInput) {
    bool result = true;
    tetris.create();

    tetris.setInputMovement(Tetris::InputDirection::LEFT);
    result = result && tetris.getInputMovement() == Tetris::InputDirection::LEFT;
    tetris.update(TetrisTest::DEFAULT_DELAY);
    result = result && tetris.getInputMovement() == Tetris::InputDirection::NONE;

    tetris.setInputRotation(Tetris::InputDirection::LEFT);
    result = result && tetris.getInputRotation() == Tetris::InputDirection::LEFT;
    tetris.update(TetrisTest::DEFAULT_DELAY);
    result = result && tetris.getInputRotation() == Tetris::InputDirection::NONE;

    tetris.setFastFall(true);
    result = result && tetris.getFastFall();
    tetris.setFastFall(false);
    result = result && !tetris.getFastFall();

    tetris.destroy();

    ASSERT_TRUE(result);
}

TEST_F(TetrisTest, MoveTetromino) {
    bool result = true;
    int x = 0;
    tetris.tetrominoUpdatedCallback = [&](const Tetromino& t) {
        auto position = t.getPosition();
        result = result && x < position.x;
        x = position.x;
    };

    tetris.create();
    tetris.setInputMovement(Tetris::InputDirection::RIGHT);
    tetris.update(TetrisTest::DEFAULT_DELAY);
    tetris.setInputMovement(Tetris::InputDirection::RIGHT);
    tetris.update(TetrisTest::DEFAULT_DELAY);

    tetris.destroy();

    ASSERT_TRUE(result);
}

TEST_F(TetrisTest, DropTetromino) {
    bool result = true;
    int y = 0;
    tetris.tetrominoUpdatedCallback = [&](const Tetromino& t) {
        auto position = t.getPosition();
        result = result && y != position.y && y < position.y;
        y = position.y;
    };

    tetris.create();

    for (int i = 0; i < 5; ++i) {
        tetris.update(TetrisTest::DEFAULT_DELAY);
    }

    tetris.destroy();

    ASSERT_TRUE(result);
}

TEST_F(TetrisTest, TetrisWorldUpdated) {
    bool result = false;
    tetris.worldUpdatedCallback = [&](const Tetris::WorldBlockArray& w) {
        result = !checkWorldEmpty(w);
    };

    tetris.create(TetrisTest::DEFAULT_SEED);

    for (int i = 0; i < 20; ++i) {
        tetris.update(TetrisTest::DEFAULT_DELAY);
    }

    tetris.destroy();

    ASSERT_TRUE(result);
}

TEST_F(TetrisTest, GameOver) {
    bool result = false;
    tetris.gameOverCallback = [&](Tetris& t) {
        result = true;
    };

    tetris.create(TetrisTest::DEFAULT_SEED);

    for (int i = 0; i < 100; ++i) {
        tetris.update(TetrisTest::DEFAULT_DELAY);
    }

    tetris.destroy();

    ASSERT_TRUE(result);
}

TEST_F(TetrisTest, ScoreUpdated) {
    bool result = false;
    int index = 0;

    tetris.scoreUpdatedCallback = [&](const int score) {
        result = true;
    };

    tetris.create(TetrisTest::DEFAULT_SEED); 

    for (int i = 0; i < 80; ++i) { 
        if (i < 4) {
            tetris.setInputMovement(Tetris::InputDirection::RIGHT);
        }
        if (i >= 17 && i < 21) {
            tetris.setInputMovement(Tetris::InputDirection::LEFT);
        }
        if (i == 35) {
            tetris.setInputMovement(Tetris::InputDirection::LEFT); 
        }
        if (i >= 57 && i < 59) {
            if (i == 57) {
                tetris.setInputRotation(Tetris::InputDirection::LEFT);
            }
            tetris.setInputMovement(Tetris::InputDirection::RIGHT);
        }
        tetris.update(TetrisTest::DEFAULT_DELAY);
    }

    tetris.destroy();

    ASSERT_TRUE(result);
}
