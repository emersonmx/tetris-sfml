#include "Tetris/Application.hpp"

#include <SFML/Window/VideoMode.hpp>

#include "MXG/DefaultState.hpp"
#include "Tetris/States/GameState.hpp"

namespace tetris {

void Application::create() {
    int flags = sf::Style::Titlebar | sf::Style::Close;
    window_.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris", flags);

    clearState();
    states_["game_state"] = std::make_unique<GameState>(this);
    changeState("game_state");
}

void Application::destroy() {
    window_.close();
    states_.clear();
}

void Application::tick() {
    currentState()->tick();
}

mxg::State* Application::getState(const std::string& name) {
    return states_[name].get();
}

void Application::changeState(const std::string& name) {
    mxg::Game::changeState(getState(name));
}

} /* namespace tetris */
