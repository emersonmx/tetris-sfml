#ifndef TETRIS_STATES_GAMESTATE_HPP_
#define TETRIS_STATES_GAMESTATE_HPP_

#include "Tetris/States/DefaultState.hpp"

namespace tetris {

class GameState : public DefaultState {
    public:
        using DefaultState::DefaultState;
};

} /* namespace tetris */
#endif /* TETRIS_STATES_GAMESTATE_HPP_ */
