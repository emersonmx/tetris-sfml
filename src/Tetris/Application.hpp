#ifndef TETRIS_APPLICATION_HPP_
#define TETRIS_APPLICATION_HPP_

#include <memory>
#include <unordered_map>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <MXG/Game.hpp>

#include "Tetris/Assets.hpp"

namespace tetris {

class Application : public mxg::Game {
    public:
        static const int WINDOW_WIDTH = 640;
        static const int WINDOW_HEIGHT = 480;

        sf::RenderWindow& window() { return window_; }
        Assets& assets() { return assets_; }

    protected:
        void create() override;
        void destroy() override;

        void tick() override;

        mxg::State* getState(const std::string& name);

        void changeState(const std::string& name);

        sf::RenderWindow window_;
        Assets assets_;

    private:
        std::unordered_map< std::string, std::unique_ptr<mxg::State> > states_;
};

} /* namespace tetris */
#endif /* TETRIS_APPLICATION_HPP_ */
