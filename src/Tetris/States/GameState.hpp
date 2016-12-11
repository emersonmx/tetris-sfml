#ifndef TETRIS_STATES_GAMESTATE_HPP_
#define TETRIS_STATES_GAMESTATE_HPP_

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
        void restart();

    protected:
        void beginTick() override;
        void processEvent(const sf::Event& event) override;
        void update() override;
        void render(sf::RenderTarget& renderTarget) override;
        void endTick() override;

    private:
        void setupGameMenu();
        void setupGameOver();
        void setupScores();
        void setupBlockRenderers();

        struct Impl;
        std::unique_ptr<Impl> impl_;
};

} /* namespace states */
} /* namespace tetris */
#endif /* TETRIS_STATES_GAMESTATE_HPP_ */
