#include "Tetris/States/DefaultState.hpp"

#include "SFML/Window/Window.hpp"

#include "Tetris/App.hpp"

namespace tetris {
namespace states {

void DefaultState::tick() {
    beginTick();
    processEvents();
    update();
    render();
    endTick();
}

void DefaultState::processEvents() {
    sf::Event event;
    auto& window = app_.getWindow();

    while (window.pollEvent(event)) {
        processEvent(event);
    }
}

void DefaultState::render() {
    auto& window = app_.getWindow();

    window.clear(sf::Color(0, 0, 0));
    render(window);
    window.display();
}

void DefaultState::processEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        app_.exit();
    }
}

} /* namespace states */
} /* namespace tetris */
