#ifndef TETRIS_STATES_DEFAULTSTATE_HPP_
#define TETRIS_STATES_DEFAULTSTATE_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "mxg/DefaultState.hpp"

namespace tetris {

class Application;

class DefaultState: public mxg::DefaultState {
    public:
        DefaultState(Application* app) : app_(app) {}

        Application* app() { return app_; }

        void tick() override;

    protected:
        virtual void beginTick() {}
        virtual void processEvents();
        virtual void update() {}
        virtual void render();
        virtual void endTick() {}

        virtual void processEvent(const sf::Event& event);
        virtual void render(sf::RenderTarget& renderTarget) {}

    private:
        Application* app_;
};

} /* namespace tetris */
#endif /* TETRIS_STATES_DEFAULTSTATE_HPP_ */

