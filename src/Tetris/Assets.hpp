#ifndef TETRIS_ASSETS_HPP_
#define TETRIS_ASSETS_HPP_

#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tetris {

class Assets {
    public:
        virtual ~Assets() {}

        void loadAssets();
};

} /* namespace tetris */
#endif /* TETRIS_ASSETS_HPP_ */
