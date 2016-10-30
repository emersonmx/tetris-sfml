#include "Tetris/States/GameState.hpp"

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

    sf::Vector2f aux{};
    int uiCenterPosition = 448;
    auto& defaultFont = assets.getDefaultFont();

    sf::Color defaultFontColor{255, 255, 255};
    sf::Color backgroundShapeColor{254,127,45};
    sf::Color gameAreaShapeColor{253,226,154};
    sf::Color nextShapeColor{252,202,70};
    int defaultFontSize = 28;

    //blockRenderer_.create(assets);
    impl_->gridSprite.setTexture(assets.getGrid());

    impl_->gameAreaShape.setSize({
        App::TILE_SIZE * Tetris::WORLD_WIDTH,
        App::TILE_SIZE * Tetris::WORLD_HEIGHT
    });
    impl_->gameAreaShape.setPosition(0, 0);
    impl_->gameAreaShape.setFillColor(gameAreaShapeColor);

    impl_->backgroundShape.setSize({
        App::WINDOW_WIDTH, App::WINDOW_HEIGHT
    });
    impl_->backgroundShape.setPosition(0, 0);
    impl_->backgroundShape.setFillColor(backgroundShapeColor);

    impl_->nextShape.setSize({128, 128});
    impl_->nextShape.setPosition(384, App::TILE_SIZE*13);
    impl_->nextShape.setFillColor(nextShapeColor);

    impl_->highScoreText.setFont(defaultFont);
    impl_->highScoreText.setCharacterSize(defaultFontSize);
    impl_->highScoreText.setFillColor(defaultFontColor);
    impl_->highScoreText.setString("HI-SCORE");
    aux = calculateCenterOfRect(impl_->highScoreText.getLocalBounds());
    impl_->highScoreText.setOrigin(aux);
    impl_->highScoreText.setPosition(uiCenterPosition, 49);

    impl_->highScoreValueText.setFont(defaultFont);
    impl_->highScoreValueText.setCharacterSize(defaultFontSize);
    impl_->highScoreValueText.setFillColor(defaultFontColor);
    impl_->highScoreValueText.setString("00000000");
    aux = calculateCenterOfRect(impl_->highScoreValueText.getLocalBounds());
    impl_->highScoreValueText.setOrigin(aux);
    impl_->highScoreValueText.setPosition(uiCenterPosition, 80);

    impl_->scoreText.setFont(defaultFont);
    impl_->scoreText.setCharacterSize(defaultFontSize);
    impl_->scoreText.setFillColor(defaultFontColor);
    impl_->scoreText.setString("SCORE");
    aux = calculateCenterOfRect(impl_->scoreText.getLocalBounds());
    impl_->scoreText.setOrigin(aux);
    impl_->scoreText.setPosition(uiCenterPosition, 112);

    impl_->scoreValueText.setFont(defaultFont);
    impl_->scoreValueText.setCharacterSize(defaultFontSize);
    impl_->scoreValueText.setFillColor(defaultFontColor);
    impl_->scoreValueText.setString("00000000");
    aux = calculateCenterOfRect(impl_->scoreValueText.getLocalBounds());
    impl_->scoreValueText.setOrigin(aux);
    impl_->scoreValueText.setPosition(uiCenterPosition, 144);

    int infoTextSize = static_cast<int>(impl_->infoText.size());
    int infoTextBaseY = 240;
    for (int i = 0; i < infoTextSize; ++i) {
        auto& text = impl_->infoText[i];
        text.setFont(defaultFont);
        text.setCharacterSize(defaultFontSize);
        text.setFillColor(defaultFontColor);
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
        aux = calculateCenterOfRect(text.getLocalBounds());
        text.setOrigin(aux);
        text.setPosition(uiCenterPosition, infoTextBaseY + 32 * i);
    }

    impl_->nextText.setFont(defaultFont);
    impl_->nextText.setCharacterSize(defaultFontSize);
    impl_->nextText.setFillColor(defaultFontColor);
    impl_->nextText.setString("NEXT");
    aux = calculateCenterOfRect(impl_->nextText.getLocalBounds());
    impl_->nextText.setOrigin(aux);
    impl_->nextText.setPosition(uiCenterPosition, 400);

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
    renderTarget.draw(impl_->gameAreaObject);
}

void GameState::setupBlockRenderers() {
    auto& blockTexture = getApp().getAssets().getBlock();
    impl_->tetrominoObject.create(blockTexture);
    impl_->world.tetrominoUpdatedCallback = [&] (const Tetromino& tetromino) {
        impl_->tetrominoObject.updateTetromino(tetromino);
    };
    impl_->gameAreaObject.create(blockTexture);
    impl_->world.worldUpdatedCallback = [&] (const Tetris::WorldBlockArray& blocks) {
        impl_->gameAreaObject.updateWorld(blocks);
    };
}

} /* namespace states */
} /* namespace tetris */
