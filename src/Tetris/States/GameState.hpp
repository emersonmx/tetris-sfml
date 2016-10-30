#ifndef TETRIS_STATES_GAMESTATE_HPP_
#define TETRIS_STATES_GAMESTATE_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Tetris/States/DefaultState.hpp"

namespace tetris {
namespace states {

class GameState : public DefaultState {
    public:
        using DefaultState::DefaultState;

        GameState(App& app);
        virtual ~GameState();

        void create() override;
        void destroy() override;

    protected:
        void beginTick() override;
        void processEvent(const sf::Event& event) override;
        void update() override;
        void render(sf::RenderTarget& renderTarget) override;

    private:
        void setupBlockRenderers();

        struct Impl;
        std::unique_ptr<Impl> impl_;
};

} /* namespace states */
} /* namespace tetris */
#endif /* TETRIS_STATES_GAMESTATE_HPP_ */
