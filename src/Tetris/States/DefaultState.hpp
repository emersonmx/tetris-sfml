#ifndef TETRIS_STATES_DEFAULTSTATE_HPP_
#define TETRIS_STATES_DEFAULTSTATE_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "mxg/DefaultState.hpp"

namespace tetris {
class App;

namespace states {

class DefaultState: public mxg::DefaultState {
    public:
        DefaultState(App& app) : app_(app) {}

        App& getApp() { return app_; }

        void tick() override;

    protected:
        virtual void beginTick() {}
        virtual void processEvents();
        virtual void update() {}
        virtual void render();
        virtual void endTick() {}

        virtual void processEvent(const sf::Event& event);
        virtual void render(sf::RenderTarget& renderTarget) = 0;

    private:
        App& app_;
};

} /* namespace states */
} /* namespace tetris */
#endif /* TETRIS_STATES_DEFAULTSTATE_HPP_ */

