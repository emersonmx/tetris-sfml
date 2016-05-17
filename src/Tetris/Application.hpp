#ifndef TETRIS_APPLICATION_HPP_
#define TETRIS_APPLICATION_HPP_

#include <MXG/Game.hpp>

namespace tetris {

class Application : public mxg::Game {
    protected:
        void create() override;
        void destroy() override;

        void tick() override;
};

} /* namespace tetris */
#endif /* TETRIS_APPLICATION_HPP_ */
