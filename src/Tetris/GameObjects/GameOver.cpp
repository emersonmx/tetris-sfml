#include "Tetris/GameObjects/GameOver.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Tetris/Utils.hpp"

namespace tetris {
namespace gameobjects {

void GameOver::create() {
    sf::Text text("GAME OVER", *font_, characterSize_);
    text.setFillColor(foregroundColor_);
    auto origin = tetris::utils::calculateCenterOfRect(text.getLocalBounds());
    text.setOrigin(origin);
    text_ = text;

    background_.setFillColor(backgroundColor_);
    auto size = tetris::utils::calculateSizeOfRect(text.getLocalBounds());
    size.x += 64;
    size.y += 20;
    background_.setSize(size);
    origin = tetris::utils::calculateCenterOfRect(background_.getLocalBounds());
    background_.setOrigin(origin);
}

void GameOver::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!getActive()) {
        return;
    }

    states.transform *= getTransform();

    target.draw(background_, states);
    target.draw(text_, states);
}

} /* namespace gameobjects */
} /* namespace tetris */
