#include "Tetris/Application.hpp"

#include <SFML/Window/VideoMode.hpp>

#include "mxg/DefaultState.hpp"
#include "Tetris/States/GameState.hpp"

namespace tetris {

void Application::create() {
    int flags = sf::Style::Titlebar | sf::Style::Close;
    window_.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris", flags);
    window_.setFramerateLimit(FRAMES_PER_SECOND);

    assets_.loadAssets();

    clearState();

    auto gameState = std::make_unique<GameState>(this);
    gameState->create();
    states_[static_cast<int>(State::GAME)] = std::move(gameState);
    changeState(State::GAME);
}

void Application::destroy() {
    states_ = {};
    window_.close();
}

void Application::tick() {
    state()->tick();
}

mxg::State* Application::getState(const State state) {
    return states_[static_cast<int>(state)].get();
}

void Application::changeState(const State state) {
    mxg::Game::changeState(getState(state));
}

} /* namespace tetris */
