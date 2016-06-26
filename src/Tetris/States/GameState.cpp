#include "Tetris/States/GameState.hpp"

#include <iostream>

#include "Tetris/Application.hpp"

namespace tetris {

void GameState::create() {
    blockRenderer_.create(app()->assets());

    world_.addListener(&blockRenderer_);
    world_.create();
}

void GameState::destroy() {
    world_.destroy();
}

void GameState::beginTick() {
    deltaTime_ = clock_.restart().asSeconds();
}

void GameState::processEvent(const sf::Event& event) {
    DefaultState::processEvent(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            world_.setInputMovement(Tetris::InputDirection::LEFT);
        } else if (event.key.code == sf::Keyboard::Right) {
            world_.setInputMovement(Tetris::InputDirection::RIGHT);
        }
        if (event.key.code == sf::Keyboard::Z) {
            world_.setInputRotation(Tetris::InputDirection::LEFT);
        } else if (event.key.code == sf::Keyboard::X) {
            world_.setInputRotation(Tetris::InputDirection::RIGHT);
        }
    }
}

void GameState::update() {
    world_.setFastFall(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    world_.update(deltaTime_);
}

void GameState::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(blockRenderer_);
}

} /* namespace tetris */
