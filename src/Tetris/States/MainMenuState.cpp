#include "Tetris/States/MainMenuState.hpp"

#include <iostream>

#include "Tetris/App.hpp"

namespace tetris {
namespace states {

MainMenuState::MainMenuState(App& app)
    : DefaultState(app) {}

MainMenuState::~MainMenuState() = default;

void MainMenuState::create() {
}

void MainMenuState::destroy() {
}

void MainMenuState::processEvent(const sf::Event& event) {
    DefaultState::processEvent(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Return) {
            gameStart_ = true;
        }
    }
}

void MainMenuState::update() {
}

void MainMenuState::render(sf::RenderTarget& renderTarget)  {
}

void MainMenuState::endTick() {
    if (gameStart_) {
        getApp().changeState(App::State::GAME);
    }
}

} /* namespace states */
} /* namespace tetris */
