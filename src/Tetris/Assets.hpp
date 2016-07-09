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
        sf::Texture& background() { return background_; }

        void loadAssets();

    private:
        sf::Texture loadTextureFromFile(const std::string& filename);

        sf::Texture block_;
        sf::Texture background_;
};

} /* namespace tetris */
#endif /* TETRIS_ASSETS_HPP_ */
