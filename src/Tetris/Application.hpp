#ifndef TETRIS_APPLICATION_HPP_
#define TETRIS_APPLICATION_HPP_

#include <memory>
#include <array>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <mxg/Game.hpp>

#include "Tetris/Defs.hpp"
#include "Tetris/Assets.hpp"
#include "Tetris/Game/Tetris.hpp"

namespace tetris {

class Application : public mxg::Game {
    public:
        enum class State {
            MENU, GAME, GAME_MENU, SIZE
        };

        static const int TILE_SIZE{32};
        static const int WINDOW_WIDTH{576};
        static const int WINDOW_HEIGHT{576};
        static const int FRAMES_PER_SECOND{60};

        sf::RenderWindow& window() { return window_; }
        Assets& assets() { return assets_; }

        mxg::State* getState(const State state);
        void changeState(const State state);

    protected:
        void create() override;
        void destroy() override;

        void tick() override;

        sf::RenderWindow window_;
        Assets assets_;

    private:
        PtrArray<mxg::State, static_cast<int>(State::SIZE)> states_;
};

} /* namespace tetris */
#endif /* TETRIS_APPLICATION_HPP_ */
