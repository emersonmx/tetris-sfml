#include "Tetris/States/GameState.hpp"

#include <iostream>

#include "Tetris/Application.hpp"
#include "Tetris/Utils.hpp"

namespace tetris {

void GameState::create() {
    sf::Vector2f aux{};
    int uiCenterPosition = 448;
    auto& defaultFont = app()->assets().defaultFont();

    blockRenderer_.create(app()->assets());
    gridSprite_.setTexture(app()->assets().grid());

    gameAreaShape_.setSize({
        Application::TILE_SIZE * Tetris::WORLD_WIDTH,
        Application::TILE_SIZE * Tetris::WORLD_HEIGHT
    });
    gameAreaShape_.setPosition(0, 0);
    gameAreaShape_.setFillColor({71, 114, 134});

    backgroundShape_.setSize({
        Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT
    });
    backgroundShape_.setPosition(0, 0);
    backgroundShape_.setFillColor({3, 37, 54});

    nextShape_.setSize({128, 128});
    nextShape_.setPosition(384, Application::TILE_SIZE*13);
    nextShape_.setFillColor({17, 60, 82});

    highScoreText_.setFont(defaultFont);
    highScoreText_.setCharacterSize(18);
    highScoreText_.setColor({110, 145, 161});
    highScoreText_.setString("HI-SCORE");
    aux = Utils::calculateCenterOfRect(highScoreText_.getLocalBounds());
    highScoreText_.setOrigin(aux);
    highScoreText_.setPosition(uiCenterPosition, 49);

    highScoreValueText_.setFont(defaultFont);
    highScoreValueText_.setCharacterSize(18);
    highScoreValueText_.setColor({110, 145, 161});
    highScoreValueText_.setString("00000000");
    aux = Utils::calculateCenterOfRect(highScoreValueText_.getLocalBounds());
    highScoreValueText_.setOrigin(aux);
    highScoreValueText_.setPosition(uiCenterPosition, 80);

    scoreText_.setFont(defaultFont);
    scoreText_.setCharacterSize(18);
    scoreText_.setColor({110, 145, 161});
    scoreText_.setString("SCORE");
    aux = Utils::calculateCenterOfRect(scoreText_.getLocalBounds());
    scoreText_.setOrigin(aux);
    scoreText_.setPosition(uiCenterPosition, 112);

    scoreValueText_.setFont(defaultFont);
    scoreValueText_.setCharacterSize(18);
    scoreValueText_.setColor({110, 145, 161});
    scoreValueText_.setString("00000000");
    aux = Utils::calculateCenterOfRect(scoreValueText_.getLocalBounds());
    scoreValueText_.setOrigin(aux);
    scoreValueText_.setPosition(uiCenterPosition, 144);

    int infoTextSize = static_cast<int>(infoText_.size());
    int infoTextBaseY = 240;
    for (int i = 0; i < infoTextSize; ++i) {
        auto& text = infoText_[i];
        text.setFont(defaultFont);
        text.setCharacterSize(18);
        text.setColor({110, 145, 161});
        switch (i) {
            case 0:
                text.setString("Press");
                break;
            case 1:
                text.setString("Enter to");
                break;
            case 2:
                text.setString("menu");
                break;
        }
        aux = Utils::calculateCenterOfRect(text.getLocalBounds());
        text.setOrigin(aux);
        text.setPosition(uiCenterPosition, infoTextBaseY + 32 * i);
    }

    nextText_.setFont(defaultFont);
    nextText_.setCharacterSize(18);
    nextText_.setColor({110, 145, 161});
    nextText_.setString("NEXT");
    aux = Utils::calculateCenterOfRect(nextText_.getLocalBounds());
    nextText_.setOrigin(aux);
    nextText_.setPosition(uiCenterPosition, 400);

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
        if (event.key.code == sf::Keyboard::Return) {
            paused_ = !paused_;
        }
    }
}

void GameState::update() {
    if (!paused_) {
        world_.setFastFall(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
        world_.update(deltaTime_);
    }
}

void GameState::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(backgroundShape_);
    renderTarget.draw(gameAreaShape_);
    renderTarget.draw(gridSprite_);
    renderTarget.draw(nextShape_);
    renderTarget.draw(highScoreText_);
    renderTarget.draw(highScoreValueText_);
    renderTarget.draw(scoreText_);
    renderTarget.draw(scoreValueText_);
    for (auto& info : infoText_) {
        renderTarget.draw(info);
    }
    renderTarget.draw(nextText_);
    renderTarget.draw(blockRenderer_);
}

} /* namespace tetris */
