#ifndef TETRIS_STATES_GAMESTATE_HPP_
#define TETRIS_STATES_GAMESTATE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Tetris/States/DefaultState.hpp"
#include "Tetris/Game/Tetris.hpp"
#include "Tetris/BlockRenderer.hpp"

namespace tetris {

class GameState : public DefaultState {
    public:
        using DefaultState::DefaultState;

        void create() override;
        void destroy() override;

    protected:
        void beginTick() override;
        void processEvent(const sf::Event& event) override;
        void update() override;
        void render(sf::RenderTarget& renderTarget) override;

    private:
        Tetris world_{};
        BlockRenderer blockRenderer_{};
        sf::Sprite gridSprite_{};
        sf::RectangleShape gameAreaShape_{};
        sf::RectangleShape backgroundShape_{};
        sf::RectangleShape nextShape_{};

        sf::Text highScoreText_{};
        sf::Text highScoreValueText_{};
        sf::Text scoreText_{};
        sf::Text scoreValueText_{};
        sf::Text nextText_{};
        std::array<sf::Text, 3> infoText_{};

        sf::Clock clock_{};
        float deltaTime_{0.0f};
};

} /* namespace tetris */
#endif /* TETRIS_STATES_GAMESTATE_HPP_ */
