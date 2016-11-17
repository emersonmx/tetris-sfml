#ifndef TETRIS_APP_HPP_
#define TETRIS_APP_HPP_

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "mxg/Game.hpp"

#include "Tetris/Defs.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {

class App : public mxg::Game {
    public:
        enum class State {
            MAIN_MENU, GAME, SIZE
        };

        static const int TILE_SIZE{32};
        static const int WINDOW_WIDTH{576};
        static const int WINDOW_HEIGHT{576};
        static const int FRAMES_PER_SECOND{60};

        sf::RenderWindow& getWindow() { return window_; }
        Assets& getAssets() { return assets_; }

        mxg::State* getState(const State state);
        void changeState(const State state);

    protected:
        void create() override;
        void destroy() override;
        void tick() override;

        sf::RenderWindow window_;
        Assets assets_;

    private:
        void setupStates();

        PtrArray<mxg::State, static_cast<int>(State::SIZE)> states_;
};

} /* namespace tetris */
#endif /* TETRIS_APP_HPP_ */
