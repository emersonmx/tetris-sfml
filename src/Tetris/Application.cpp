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

mxg::State* Application::getState(const std::string& name) {
    return states_[name].get();
}

void Application::changeState(const std::string& name) {
    mxg::Game::changeState(getState(name));
}

} /* namespace tetris */
