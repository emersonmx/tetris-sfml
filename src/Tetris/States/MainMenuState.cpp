#include "Tetris/States/MainMenuState.hpp"

#include <iostream>

#include <SFML/Audio/Music.hpp>

#include "Tetris/App.hpp"
#include "Tetris/Utils.hpp"

namespace tetris {
namespace states {

MainMenuState::MainMenuState(App& app)
    : DefaultState(app) {}

MainMenuState::~MainMenuState() = default;

void MainMenuState::create() {
    auto& assets = getApp().getAssets();
    auto& defaultFont = assets.getDefaultFont();

    mainMenuSprite_.setTexture(assets.getMainMenuTexture());
    gameStartText.setFont(defaultFont);
    gameStartText.setCharacterSize(28);
    gameStartText.setFillColor(sf::Color::White);
    gameStartText.setString("PRESS ANY KEY TO START");
    auto aux = tetris::utils::calculateCenterOfRect(
        gameStartText.getLocalBounds());
    gameStartText.setOrigin(aux);
    gameStartText.setPosition({App::WINDOW_WIDTH / 2.0f, App::WINDOW_HEIGHT / 1.3f});

    auto& music = getApp().getAssets().getMainMusic();
    music.setVolume(70);
    music.play();
}

void MainMenuState::destroy() {
}

void MainMenuState::processEvent(const sf::Event& event) {
    DefaultState::processEvent(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Return) {
            auto& sound = getApp().getAssets().getGameStartSound();
            sound.play();

            clock_.restart();
            gameStart_ = true;
        }
    }
}

void MainMenuState::update() {
}

void MainMenuState::render(sf::RenderTarget& renderTarget)  {
    renderTarget.draw(mainMenuSprite_);
    renderTarget.draw(gameStartText);
}

void MainMenuState::endTick() {
    auto timer = clock_.getElapsedTime();
    if (timer.asSeconds() > 0.5f && gameStart_) {
        getApp().changeState(App::State::GAME);
    }
}

} /* namespace states */
} /* namespace tetris */
