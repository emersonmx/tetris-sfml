#ifndef TETRIS_GAMEOBJECTS_GAMEOVER_HPP_
#define TETRIS_GAMEOBJECTS_GAMEOVER_HPP_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Tetris/GameObjects/GameObject.hpp"

namespace tetris {
namespace gameobjects {

class GameOver : public GameObject {
    public:
        sf::Font& getFont() const { return *font_; }
        void setFont(sf::Font& font) { font_ = &font; }
        sf::Color getBackgroundColor() const { return backgroundColor_; }
        void setBackgroundColor(const sf::Color& color) {
            backgroundColor_ = color;
        }
        sf::Color getForegroundColor() const { return foregroundColor_; }
        void setForegroundColor(const sf::Color& color) {
            foregroundColor_ = color;
        }
        std::size_t getCharacterSize() const { return characterSize_; }
        void setCharacterSize(const std::size_t characterSize) {
            characterSize_ = characterSize;
        }

        void create();

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Font* font_;
        sf::RectangleShape background_;
        sf::Text text_;
        sf::Color backgroundColor_;
        sf::Color foregroundColor_;
        std::size_t characterSize_;
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_GAMEOVER_HPP_ */
