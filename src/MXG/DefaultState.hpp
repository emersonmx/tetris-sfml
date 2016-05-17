#ifndef MXG_DEFAULTSTATE_HPP_
#define MXG_DEFAULTSTATE_HPP_

#include "MXG/State.hpp"

namespace mxg {

class DefaultState: public State {
    public:
        void create() override {}
        void destroy() override {}

        void enter() override {}
        void exit() override {}

        void tick() override {}
};

} /* namespace mxg */
#endif /* MXG_DEFAULTSTATE_HPP_ */
