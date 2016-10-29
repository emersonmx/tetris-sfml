#ifndef TETRIS_STATES_GAMESTATE_HPP_
#define TETRIS_STATES_GAMESTATE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>

#include "Tetris/States/DefaultState.hpp"

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
};

} /* namespace tetris */
#endif /* TETRIS_STATES_GAMESTATE_HPP_ */
