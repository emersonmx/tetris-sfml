#include "Tetris/States/DefaultState.hpp"

#include <iostream>

#include "SFML/Window/Window.hpp"

#include "Tetris/Application.hpp"

namespace tetris {

void DefaultState::tick() {
    beginTick();
    processEvents();
    update();
    render();
    endTick();
}

void DefaultState::processEvents() {
    sf::Event event;
    sf::Window& window = app_->window();
    while (window.pollEvent(event)) {
        processEvent(event);
    }
}

void DefaultState::render() {
    sf::RenderWindow& window = app_->window();
    window.clear(sf::Color(64, 64, 64));
    render(window);
    window.display();
}

void DefaultState::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        app_->exit();
    }
}

} /* namespace tetris */
