#include "Tetris/App.hpp"

#include <memory>

#include "SFML/Window/VideoMode.hpp"

#include "mxg/DefaultState.hpp"

#include "Tetris/States/GameState.hpp"

namespace tetris {

mxg::State* App::getState(const State state) {
    return states_[static_cast<int>(state)].get();
}

void App::changeState(const State state) {
    auto nextState = getState(state);
    setState(*nextState);
}

void App::create() {
    int flags = sf::Style::Titlebar | sf::Style::Close;
    window_.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris", flags);
    window_.setFramerateLimit(FRAMES_PER_SECOND);

    assets_.loadAssets();

    setupStates();
}

void App::destroy() {
    states_ = {};
    window_.close();
}

void App::tick() {
    mxg::Game::getState()->tick();
}

void App::setupStates() {
    using namespace tetris::states;

    clearState();

    auto gameState = std::make_unique<GameState>(*this);
    gameState->create();
    states_[static_cast<int>(State::GAME)] = std::move(gameState);
    changeState(State::GAME);
}

} /* namespace tetris */
