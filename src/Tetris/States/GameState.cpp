#include "Tetris/States/GameState.hpp"

#include "Tetris/App.hpp"
#include "Tetris/Utils.hpp"

namespace tetris {

void GameState::create() {
}

void GameState::destroy() {
}

void GameState::beginTick() {
}

void GameState::processEvent(const sf::Event& event) {
    DefaultState::processEvent(event);
}

void GameState::update() {
}

void GameState::render(sf::RenderTarget& renderTarget) {
}


} /* namespace tetris */
