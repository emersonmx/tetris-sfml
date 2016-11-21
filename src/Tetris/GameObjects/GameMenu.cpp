#include "Tetris/GameObjects/GameMenu.hpp"

#include <algorithm>
#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Tetris/Utils.hpp"

namespace tetris {
namespace gameobjects {

void GameMenu::setSelected(const int selected) {
    int size = static_cast<int>(options_.size()) - 1;
    if (selected < 0) {
        selected_ = 0;
    } else if (selected > size) {
        selected_ = size;
    } else {
        selected_ = selected;
    }
}

void GameMenu::next() {
    setSelected(selected_ + 1);
    update();
}

void GameMenu::previous() {
    setSelected(selected_ - 1);
    update();
}

void GameMenu::create() {
    int optionsSize = static_cast<int>(options_.size());
    if (optionsSize <= 0) {
        return;
    }

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f center;
    sf::FloatRect bounds;

    textArray_.clear();
    for (auto& option : options_) {
        sf::Text text(option, *font_, characterSize_);
        textArray_.emplace_back(text);
    }

    float textHeight = getTextHeight();
    float totalHeight = getTotalHeight();

    for (int i = 0; i < optionsSize; i++) {
        sf::Text& text = textArray_.at(i);
        position = text.getPosition();
        position.y = textHeight * i + (lineSpacing_ * i);
        text.setPosition(position);
    }

    setOrigin(0, totalHeight / 2.0f);
    update();
}

float GameMenu::getTextHeight() {
    sf::Text& first = textArray_.at(0);
    auto bounds = first.getLocalBounds();
    return bounds.height;
}

float GameMenu::getTotalHeight() {
    int optionsSize = static_cast<int>(options_.size());
    if (optionsSize <= 0) {
        return 0;
    }

    float textHeight = getTextHeight();
    return textHeight * optionsSize + (lineSpacing_ * (optionsSize - 1));
}

void GameMenu::update() {
    updateTexts();
    updateBackground();
}

void GameMenu::updateTexts() {
    int size = static_cast<int>(options_.size());
    for (int i = 0; i < size; i++) {
        sf::Text& text = textArray_.at(i);
        if (selected_ == i) {
            text.setFillColor(selectColor_);
        } else {
            text.setFillColor(foregroundColor_);
        }
        updateTextCenter(text);
    }
}

void GameMenu::updateTextCenter(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    sf::Vector2f center = tetris::utils::calculateCenterOfRect(bounds);
    center.y = bounds.top;
    text.setOrigin(center);
}

void GameMenu::updateBackground() {
    float totalHeight = getTotalHeight();

    float paddingTop = padding_[static_cast<int>(Padding::TOP)];
    float paddingRight = padding_[static_cast<int>(Padding::RIGHT)];
    float paddingBottom = padding_[static_cast<int>(Padding::BOTTOM)];
    float paddingLeft = padding_[static_cast<int>(Padding::LEFT)];

    background_.setFillColor(backgroundColor_);
    background_.setSize({
        width_ + paddingLeft + paddingRight,
        totalHeight + paddingTop + paddingBottom
    });
    auto bounds = background_.getLocalBounds();
    sf::Vector2f center = tetris::utils::calculateCenterOfRect(bounds);
    background_.setOrigin(center);
    background_.setPosition({0, totalHeight / 2.0f});
}

void GameMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!getActive()) {
        return;
    }

    states.transform *= getTransform();

    target.draw(background_, states);

    for (auto& text : textArray_) {
        target.draw(text, states);
    }
}


} /* namespace gameobjects */
} /* namespace tetris */
