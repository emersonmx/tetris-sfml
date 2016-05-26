#include <iostream>
#include "Tetris/Game/Tetromino.hpp"

using namespace tetris;

void printType(const Tetromino::Type& type) {
    std::cout << "Type: ";
    switch (type) {
        case Tetromino::Type::I:
            std::cout << "I";
            break;
        case Tetromino::Type::J:
            std::cout << "J";
            break;
        case Tetromino::Type::L:
            std::cout << "L";
            break;
        case Tetromino::Type::O:
            std::cout << "O";
            break;
        case Tetromino::Type::S:
            std::cout << "S";
            break;
        case Tetromino::Type::T:
            std::cout << "T";
            break;
        case Tetromino::Type::Z:
            std::cout << "Z";
            break;
        default:
            std::cout << "-";
    }
    std::cout << std::endl;
}

void printTetrominoAttr(const Tetromino& tetromino) {
    std::cout << "Position: " << tetromino.x << ", " << tetromino.y << std::endl;
    printType(tetromino.type());
    std::cout << "Pivot: " << tetromino.pivot_x << ", " << tetromino.pivot_y << std::endl;
}

void printTetromino(Tetromino& tetromino) {
    std::array<char, 16> area;
    area.fill('.');

    for (auto block : tetromino.getBlocks()) {
        area[block.y * 4 + block.x] = '#';
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << area[i * 4 + j];
        }
        std::cout << std::endl;
    }
}

void printDirection(int rotation) {
    switch (rotation) {
        case 0:
            std::cout << "Up";
            break;
        case 1:
            std::cout << "Right";
            break;
        case 2:
            std::cout << "Down";
            break;
        case 3:
            std::cout << "Left";
            break;
        default:
            std::cout << "WTF? O,o" << std::endl;
    }
}

int main() {
    Tetromino t{{
        Tetromino::BlockArray {{
            {0, 2}, {1, 2}, {2, 2}, {1, 1}
        }},
        Tetromino::BlockArray {{
            {1, 1}, {1, 2}, {1, 3}, {2, 2}
        }},
        Tetromino::BlockArray {{
            {0, 2}, {1, 2}, {2, 2}, {1, 3}
        }},
        Tetromino::BlockArray {{
            {1, 1}, {1, 2}, {1, 3}, {0, 2}
        }},
    }, Tetromino::Type::T};

    std::cout << "Attributes" << std::endl;
    printTetrominoAttr(t);
    std::cout << std::endl;

    std::cout << "TEST turnRight()" << std::endl;
    t.resetRotation();
    for (int i = 0; i < 4; ++i) {
        std::cout << "Direction ";
        printDirection(i % 4);
        std::cout << std::endl;
        printTetromino(t);
        t.turnRight();
        std::cout << std::endl;
    }

    std::cout << "TEST resetRotation()" << std::endl;
    t.turnRight();
    t.resetRotation();
    std::cout << "Direction ";
    printDirection(0);
    std::cout << std::endl;
    printTetromino(t);
    std::cout << std::endl;

    std::cout << "TEST turnLeft()" << std::endl;
    t.resetRotation();
    for (int i = 0; i < 4; ++i) {
        std::cout << "Direction ";
        printDirection((4 - i) % 4);
        std::cout << std::endl;
        printTetromino(t);
        t.turnLeft();
        std::cout << std::endl;
    }

    return 0;
}
