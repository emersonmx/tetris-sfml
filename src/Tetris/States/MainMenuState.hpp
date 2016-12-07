#ifndef TETRIS_STATES_MAINMENUSTATE_HPP_
#define TETRIS_STATES_MAINMENUSTATE_HPP_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "Tetris/States/DefaultState.hpp"

namespace tetris {
namespace states {

class MainMenuState : public DefaultState {
    public:
        using DefaultState::DefaultState;

        MainMenuState(App& app);
        virtual ~MainMenuState();

        void create() override;
        void destroy() override;

    protected:
        void processEvent(const sf::Event& event) override;
        void update() override;
        void render(sf::RenderTarget& renderTarget) override;
        void endTick() override;

        sf::Sprite mainMenuSprite_{};
        sf::Text gameStartText{};

        sf::Clock clock_;
        bool gameStart_{false};
};

} /* namespace states */
} /* namespace tetris */
#endif /* TETRIS_STATES_MAINMENUSTATE_HPP_ */
