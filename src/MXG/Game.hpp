#ifndef MXG_GAME_HPP_
#define MXG_GAME_HPP_

#include "MXG/Application.hpp"
#include "MXG/DefaultState.hpp"

namespace mxg {

class Game : public Application {
    public:
        State* currentState() { return currentState_; }
        void changeState(State* state);
        void clearState() { currentState_ = nullptr; }

    private:
        void throwExceptionIfNull(State* state);

        State* currentState_{nullptr};
};

} /* namespace mxg */
#endif /* MXG_GAME_HPP_ */
