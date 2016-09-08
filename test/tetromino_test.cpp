#include "gtest/gtest.h"

#include "Tetris/Game/Tetromino.hpp"

using namespace tetris;

void printTetromino(Tetromino& tetromino) {
    std::array<char, 16> area;
    area.fill('.');

    for (auto block : tetromino.getBlocks()) {
        area[block.x * 4 + block.y] = '#';
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << area[j * 4 + i];
        }
        std::cout << std::endl;
    }
}

TEST(TetrominoTest, CreateEmptyTetromino) {
    Tetromino tetromino{};
    auto pivot = tetromino.getPivot();
    bool result = true;
    for (auto block : tetromino.getBlocks()) {
        result = result && block.x == -pivot.x && block.y == -pivot.y;
    }
    ASSERT_TRUE(result);
}

TEST(TetrominoTest, Move) {
    Tetromino tetromino{};

    tetromino.move({1, 2});
    auto position = tetromino.getPosition();

    ASSERT_TRUE(position.x == 1 && position.y == 2);
}

TEST(TetrominoTest, LoadRotationsFromIntArray) {
    Tetromino tetromino{};
    tetromino.move(tetromino.getPivot());
    tetromino.loadRotationsFromIntArray({
        // T
        5, 8, 9, 10
    });

    auto blocks = tetromino.getBlocks();
    bool result = true && blocks[0].x == 1 && blocks[0].y == 1;
    result = result && blocks[1].x == 0 && blocks[1].y == 2;
    result = result && blocks[2].x == 1 && blocks[2].y == 2;
    result = result && blocks[3].x == 2 && blocks[3].y == 2;

    //printTetromino(tetromino);

    ASSERT_TRUE(result);
}

TEST(TetrominoTest, RotateLeft) {
    Tetromino tetromino{};
    tetromino.move(tetromino.getPivot());
    tetromino.loadRotationsFromIntArray({
        // T
        5,8,9,10,
        5,9,10,13,
        8,9,10,13,
        5,8,9,13
    });
    tetromino.rotateLeft();

    auto blocks = tetromino.getBlocks();
    bool result = true && blocks[0].x == 1 && blocks[0].y == 1;
    result = result && blocks[1].x == 0 && blocks[1].y == 2;
    result = result && blocks[2].x == 1 && blocks[2].y == 2;
    result = result && blocks[3].x == 1 && blocks[3].y == 3;

    //printTetromino(tetromino);

    ASSERT_TRUE(result);
}

TEST(TetrominoTest, RotateRight) {
    Tetromino tetromino{};
    tetromino.move(tetromino.getPivot());
    tetromino.loadRotationsFromIntArray({
        // T
        5,8,9,10,
        5,9,10,13,
        8,9,10,13,
        5,8,9,13
    });
    tetromino.rotateRight();

    auto blocks = tetromino.getBlocks();
    bool result = true && blocks[0].x == 1 && blocks[0].y == 1;
    result = result && blocks[1].x == 1 && blocks[1].y == 2;
    result = result && blocks[2].x == 2 && blocks[2].y == 2;
    result = result && blocks[3].x == 1 && blocks[3].y == 3;

    //printTetromino(tetromino);

    ASSERT_TRUE(result);
}

TEST(TetrominoTest, FullRotateRight) {
    Tetromino tetromino{};
    tetromino.move(tetromino.getPivot());
    tetromino.loadRotationsFromIntArray({
        // T
        5,8,9,10,
        5,9,10,13,
        8,9,10,13,
        5,8,9,13
    });
    tetromino.rotateRight();
    tetromino.rotateRight();
    tetromino.rotateRight();
    tetromino.rotateRight();

    auto blocks = tetromino.getBlocks();
    bool result = true && blocks[0].x == 1 && blocks[0].y == 1;
    result = result && blocks[1].x == 0 && blocks[1].y == 2;
    result = result && blocks[2].x == 1 && blocks[2].y == 2;
    result = result && blocks[3].x == 2 && blocks[3].y == 2;

    //printTetromino(tetromino);

    ASSERT_TRUE(result);
}

TEST(TetrominoTest, FullRotateLeft) {
    Tetromino tetromino{};
    tetromino.move(tetromino.getPivot());
    tetromino.loadRotationsFromIntArray({
        // T
        5,8,9,10,
        5,9,10,13,
        8,9,10,13,
        5,8,9,13
    });
    tetromino.rotateLeft();
    tetromino.rotateLeft();
    tetromino.rotateLeft();
    tetromino.rotateLeft();

    auto blocks = tetromino.getBlocks();
    bool result = true && blocks[0].x == 1 && blocks[0].y == 1;
    result = result && blocks[1].x == 0 && blocks[1].y == 2;
    result = result && blocks[2].x == 1 && blocks[2].y == 2;
    result = result && blocks[3].x == 2 && blocks[3].y == 2;

    //printTetromino(tetromino);

    ASSERT_TRUE(result);
}
