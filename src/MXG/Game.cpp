#include "MXG/Game.hpp"

#include <stdexcept>

namespace mxg {

Game::Game() {
    states_.emplace(new DefaultState());
}

State* Game::currentState() {
    return states_.top().get();
}

void Game::pushState(State* state) {
    throwExceptionIfNull(state);

    currentState()->exit();
    state->enter();
    states_.emplace(state);
}

void Game::popState() {
    if (!statesIsEmpty()) {
        currentState()->exit();
        states_.pop();
        currentState()->enter();
    }
}

void Game::clearStates() {
    while (!statesIsEmpty()) {
        popState();
    }
}

void Game::changeState(State* state) {
    throwExceptionIfNull(state);

    popState();
    pushState(state);
}

bool Game::statesIsEmpty() {
    return states_.size() <= 1;
}

void Game::throwExceptionIfNull(State* state) {
    if (state == nullptr) {
        throw std::invalid_argument("state can be null.");
    }
}

} /* namespace mxg */
