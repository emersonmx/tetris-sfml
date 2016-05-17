#ifndef MXG_GAME_HPP_
#define MXG_GAME_HPP_

#include <memory>
#include <stack>

#include "MXG/Application.hpp"
#include "MXG/DefaultState.hpp"

namespace mxg {

class Game : public Application {
    public:
        Game();

        State* currentState();
        void pushState(State* state);
        void popState();
        void clearStates();
        void changeState(State* state);

    private:
        bool statesIsEmpty();
        void throwExceptionIfNull(State* state);

        std::stack< std::unique_ptr<State> > states_;
};

} /* namespace mxg */
#endif /* MXG_GAME_HPP_ */
