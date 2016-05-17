#include "MXG/Game.hpp"

#include <stdexcept>

namespace mxg {

void Game::changeState(State* state) {
    throwExceptionIfNull(state);

    currentState_->exit();
    state->enter();

    currentState_ = state;
}

void Game::throwExceptionIfNull(State* state) {
    if (state == nullptr) {
        throw std::invalid_argument("state can be null.");
    }
}

} /* namespace mxg */
