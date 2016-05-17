#include "Tetris/Application.hpp"

#include <iostream>

namespace tetris {

void Application::create() {
    std::cout << "Hello world" << std::endl;
    exit();
}

void Application::destroy() {
}

void Application::tick() {
}

} /* namespace tetris */
