#ifndef TETRIS_APPLICATION_HPP_
#define TETRIS_APPLICATION_HPP_

#include <memory>
#include <unordered_map>

#include <MXG/Game.hpp>

namespace tetris {

class Application : public mxg::Game {
    protected:
        void create() override;
        void destroy() override;

        void tick() override;

        mxg::State* getState(const std::string& name);

        void changeState(const std::string& name);

    private:
        std::unordered_map< std::string, std::unique_ptr<mxg::State> > states_;
};

} /* namespace tetris */
#endif /* TETRIS_APPLICATION_HPP_ */
