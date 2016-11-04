#include "Tetris/States/GameState.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Tetris/App.hpp"
#include "Tetris/Utils.hpp"
#include "Tetris/Game/Tetris.hpp"
#include "Tetris/GameObjects/Tetromino.hpp"
#include "Tetris/GameObjects/GameArea.hpp"

using namespace tetris::game;

namespace tetris {
namespace states {

struct GameState::Impl {
    tetris::game::Tetris world{};
    tetris::gameobjects::Tetromino tetrominoObject{};
    tetris::gameobjects::Tetromino nextTetrominoObject{};
    tetris::gameobjects::GameArea gameAreaObject{};
    sf::Sprite gridSprite{};
    sf::RectangleShape gameAreaShape{};
    sf::RectangleShape backgroundShape{};
    sf::RectangleShape nextShape{};

    sf::Text highScoreText{};
    sf::Text highScoreValueText{};
    sf::Text scoreText{};
    sf::Text scoreValueText{};
    sf::Text nextText{};
    std::array<sf::Text, 3> infoText{};

    sf::Color defaultFontColor{255, 255, 255};
    sf::Color backgroundShapeColor{254,127,45};
    sf::Color gameAreaShapeColor{253,226,154};
    sf::Color nextShapeColor{252,202,70};
    int defaultFontSize{28};
    int uiCenterPosition{448};
    sf::Vector2f aux{};

    sf::Clock clock{};
    float deltaTime{0.0f};
    bool paused{false};
};

GameState::GameState(App& app)
    : DefaultState(app), impl_(std::make_unique<Impl>()) {}
GameState::~GameState() = default;

void GameState::create() {
    using namespace tetris::utils;

    auto& app = getApp();
    auto& assets = app.getAssets();

    auto& defaultFont = assets.getDefaultFont();

    //blockRenderer_.create(assets);
    impl_->gridSprite.setTexture(assets.getGrid());

    impl_->gameAreaShape.setSize({
        App::TILE_SIZE * Tetris::WORLD_WIDTH,
        App::TILE_SIZE * Tetris::WORLD_HEIGHT
    });
    impl_->gameAreaShape.setPosition(0, 0);
    impl_->gameAreaShape.setFillColor(impl_->gameAreaShapeColor);

    impl_->backgroundShape.setSize({
        App::WINDOW_WIDTH, App::WINDOW_HEIGHT
    });
    impl_->backgroundShape.setPosition(0, 0);
    impl_->backgroundShape.setFillColor(impl_->backgroundShapeColor);

    impl_->nextShape.setSize({128, 128});
    impl_->nextShape.setPosition(384, App::TILE_SIZE*13);
    impl_->nextShape.setFillColor(impl_->nextShapeColor);

    setupScores();

    int infoTextSize = static_cast<int>(impl_->infoText.size());
    int infoTextBaseY = 240;
    for (int i = 0; i < infoTextSize; ++i) {
        auto& text = impl_->infoText[i];
        text.setFont(defaultFont);
        text.setCharacterSize(impl_->defaultFontSize);
        text.setFillColor(impl_->defaultFontColor);
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
        impl_->aux = tetris::utils::calculateCenterOfRect(
                text.getLocalBounds());
        text.setOrigin(impl_->aux);
        text.setPosition(impl_->uiCenterPosition, infoTextBaseY + 32 * i);
    }

    impl_->nextText.setFont(defaultFont);
    impl_->nextText.setCharacterSize(impl_->defaultFontSize);
    impl_->nextText.setFillColor(impl_->defaultFontColor);
    impl_->nextText.setString("NEXT");
    impl_->aux = tetris::utils::calculateCenterOfRect(
            impl_->nextText.getLocalBounds());
    impl_->nextText.setOrigin(impl_->aux);
    impl_->nextText.setPosition(impl_->uiCenterPosition, 400);

    setupBlockRenderers();
    impl_->world.create();
}

void GameState::destroy() {
    impl_->world.destroy();
}

void GameState::beginTick() {
    impl_->deltaTime = impl_->clock.restart().asSeconds();
}

void GameState::processEvent(const sf::Event& event) {
    DefaultState::processEvent(event);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            impl_->world.setInputMovement(Tetris::InputDirection::LEFT);
        } else if (event.key.code == sf::Keyboard::Right) {
            impl_->world.setInputMovement(Tetris::InputDirection::RIGHT);
        }
        if (event.key.code == sf::Keyboard::Z) {
            impl_->world.setInputRotation(Tetris::InputDirection::LEFT);
        } else if (event.key.code == sf::Keyboard::X) {
            impl_->world.setInputRotation(Tetris::InputDirection::RIGHT);
        }
        if (event.key.code == sf::Keyboard::Return) {
            impl_->paused = !impl_->paused;
        }
    }
}

void GameState::update() {
    if (!impl_->paused) {
        impl_->world.setFastFall(sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
        impl_->world.update(impl_->deltaTime);
    }
}

void GameState::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(impl_->backgroundShape);
    renderTarget.draw(impl_->gameAreaShape);
    renderTarget.draw(impl_->gridSprite);
    renderTarget.draw(impl_->nextShape);
    renderTarget.draw(impl_->highScoreText);
    renderTarget.draw(impl_->highScoreValueText);
    renderTarget.draw(impl_->scoreText);
    renderTarget.draw(impl_->scoreValueText);
    for (auto& info : impl_->infoText) {
        renderTarget.draw(info);
    }
    renderTarget.draw(impl_->nextText);

    renderTarget.draw(impl_->tetrominoObject);
    renderTarget.draw(impl_->nextTetrominoObject);
    renderTarget.draw(impl_->gameAreaObject);
}

void GameState::setupScores() {
    auto& defaultFont = getApp().getAssets().getDefaultFont();

    impl_->highScoreText.setFont(defaultFont);
    impl_->highScoreText.setCharacterSize(impl_->defaultFontSize);
    impl_->highScoreText.setFillColor(impl_->defaultFontColor);
    impl_->highScoreText.setString("HI-SCORE");
    impl_->aux = tetris::utils::calculateCenterOfRect(
            impl_->highScoreText.getLocalBounds());
    impl_->highScoreText.setOrigin(impl_->aux);
    impl_->highScoreText.setPosition(impl_->uiCenterPosition, 49);

    impl_->highScoreValueText.setFont(defaultFont);
    impl_->highScoreValueText.setCharacterSize(impl_->defaultFontSize);
    impl_->highScoreValueText.setFillColor(impl_->defaultFontColor);
    impl_->highScoreValueText.setString("00000000");
    impl_->aux = tetris::utils::calculateCenterOfRect(
            impl_->highScoreValueText.getLocalBounds());
    impl_->highScoreValueText.setOrigin(impl_->aux);
    impl_->highScoreValueText.setPosition(impl_->uiCenterPosition, 80);

    impl_->scoreText.setFont(defaultFont);
    impl_->scoreText.setCharacterSize(impl_->defaultFontSize);
    impl_->scoreText.setFillColor(impl_->defaultFontColor);
    impl_->scoreText.setString("SCORE");
    impl_->aux = tetris::utils::calculateCenterOfRect(
            impl_->scoreText.getLocalBounds());
    impl_->scoreText.setOrigin(impl_->aux);
    impl_->scoreText.setPosition(impl_->uiCenterPosition, 112);

    impl_->scoreValueText.setFont(defaultFont);
    impl_->scoreValueText.setCharacterSize(impl_->defaultFontSize);
    impl_->scoreValueText.setFillColor(impl_->defaultFontColor);
    impl_->scoreValueText.setString("00000000");
    impl_->aux = tetris::utils::calculateCenterOfRect(
            impl_->scoreValueText.getLocalBounds());
    impl_->scoreValueText.setOrigin(impl_->aux);
    impl_->scoreValueText.setPosition(impl_->uiCenterPosition, 144);

    impl_->world.scoreUpdatedCallback = [&] (const int score) {
        std::ostringstream buf;
        buf << std::setfill('0') << std::setw(8);
        buf << score;
        impl_->scoreValueText.setString(buf.str());
    };
    impl_->world.highScoreUpdatedCallback = [&] (const int highScore) {
        std::ostringstream buf;
        buf << std::setfill('0') << std::setw(8);
        buf << highScore;
        impl_->highScoreValueText.setString(buf.str());
    };
}

void GameState::setupBlockRenderers() {
    auto& blockTexture = getApp().getAssets().getBlock();

    impl_->tetrominoObject.create(blockTexture);
    impl_->world.tetrominoUpdatedCallback = [&] (const Tetromino& tetromino) {
        impl_->tetrominoObject.updateTetromino(tetromino);
    };

    impl_->nextTetrominoObject.create(blockTexture);
    impl_->nextTetrominoObject.setPosition(416, 480);
    impl_->world.nextTetrominoCallback = [&] (const Tetromino& tetromino) {
        impl_->nextTetrominoObject.updateTetromino(tetromino);
    };

    impl_->gameAreaObject.create(blockTexture);
    impl_->world.worldUpdatedCallback = [&] (const Tetris::WorldBlockArray& blocks) {
        impl_->gameAreaObject.updateWorld(blocks);
    };
}

} /* namespace states */
} /* namespace tetris */
