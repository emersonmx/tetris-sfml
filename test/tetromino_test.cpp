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
    Tetromino::Position position = tetromino.position();
    Tetromino::Position pivot = tetromino.pivot();
    std::cout << "Position: " << position.x << ", " << position.y << std::endl;
    printType(tetromino.type());
    std::cout << "Pivot: " << pivot.x << ", " << pivot.y << std::endl;
}

void printTetromino(Tetromino& tetromino) {
    std::array<char, 16> area;
    area.fill('.');

    for (auto block : tetromino.blocks()) {
        area[block.x * 4 + block.y] = '#';
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << area[j * 4 + i];
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
    Tetromino t{};
    t.loadRotationsFromIntArray({
        // T
        5,8,9,10,
        5,9,10,13,
        8,9,10,13,
        5,8,9,13
    });

    std::cout << "Attributes" << std::endl;
    printTetromino(t);
    std::cout << std::endl;

    std::cout << "TEST rotateRight()" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Direction ";
        printDirection(i % 4);
        std::cout << std::endl;
        printTetromino(t);
        std::cout << std::endl;
        t.rotateRight();
    }

    std::cout << "TEST rotateLeft()" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Direction ";
        printDirection((4 - i) % 4);
        std::cout << std::endl;
        printTetromino(t);
        std::cout << std::endl;
        t.rotateLeft();
    }

    return 0;
}
