#ifndef TETRIS_ASSETS_HPP_
#define TETRIS_ASSETS_HPP_

#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tetris {

class Assets {
    public:
        virtual ~Assets() {}

        sf::Texture& block() { return block_; }

        void loadAssets();

    private:
        sf::Texture& loadTextureFromFile(const std::string& filename);

        sf::Texture block_;
};

} /* namespace tetris */
#endif /* TETRIS_ASSETS_HPP_ */
