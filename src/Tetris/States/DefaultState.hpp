#ifndef TETRIS_STATES_DEFAULTSTATE_HPP_
#define TETRIS_STATES_DEFAULTSTATE_HPP_

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "mxg/DefaultState.hpp"

namespace tetris {

class Application;

class DefaultState: public mxg::DefaultState {
    public:
        DefaultState(Application* app) : app_(app) {}

        void tick() override;

    protected:
        const int FRAMES_PER_SECOND = 60;
        const float TIME_STEP = 1.0f / FRAMES_PER_SECOND;

        virtual void beginTick() {}
        virtual void processEvents();
        virtual void update() {}
        virtual void render();
        virtual void endTick() {}

        virtual void processEvent(const sf::Event& event);
        virtual void render(sf::RenderTarget& renderTarget) {}

        Application* app_;

    private:
        sf::Clock clock_;

        float timeAccumulator_{0.0f};
};

} /* namespace tetris */
#endif /* TETRIS_STATES_DEFAULTSTATE_HPP_ */

