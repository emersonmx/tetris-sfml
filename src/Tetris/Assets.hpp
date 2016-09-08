#ifndef TETRIS_ASSETS_HPP_
#define TETRIS_ASSETS_HPP_

#include <memory>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tetris {

class Assets {
    public:
        virtual ~Assets() {}

        sf::Texture& getBlock() { return block_; }
        sf::Texture& getGrid() { return grid_; }

        sf::Font& getDefaultFont() { return defaultFont_; }

        void loadAssets();

    private:
        sf::Texture loadTextureFromFile(const std::string& filename);
        sf::Font loadFontFromFile(const std::string& filename);

        sf::Texture block_;
        sf::Texture grid_;

        sf::Font defaultFont_;
};

} /* namespace tetris */
#endif /* TETRIS_ASSETS_HPP_ */
