#ifndef TETRIS_GAMEOBJECTS_GAMEMENU_HPP_
#define TETRIS_GAMEOBJECTS_GAMEMENU_HPP_

#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Tetris/GameObjects/GameObject.hpp"

namespace tetris {
namespace gameobjects {

class GameMenu : public GameObject {
    public:
        using Options = std::vector<std::string>;

        enum class Padding {
            TOP, RIGHT, BOTTOM, LEFT, SIZE
        };

        Options getOptions() const { return options_; }
        void setOptions(const Options& options) { options_ = options; }
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
        sf::Color getSelectColor() const { return selectColor_; }
        void setSelectColor(const sf::Color& color) {
            selectColor_ = color;
        }
        std::size_t getCharacterSize() const { return characterSize_; }
        void setCharacterSize(const std::size_t characterSize) {
            characterSize_ = characterSize;
        }
        std::size_t getLineSpacing() const { return lineSpacing_; }
        void setLineSpacing(const std::size_t spacing) { lineSpacing_ = spacing; }
        std::size_t getWidth() const { return width_; }
        void setWidth(const std::size_t width) { width_ = width; }
        auto getPadding() const { return padding_; }
        void setPadding(std::size_t top, std::size_t right,
                        std::size_t bottom, std::size_t left) {
            padding_ = { top, right, bottom, left };
        }
        int getSelected() const { return selected_; }
        void setSelected(const int selected);

        void next();
        void previous();
        void create();

    protected:
        float getTextHeight();
        float getTotalHeight();

        void update();
        void updateTexts();
        void updateTextCenter(sf::Text& text);
        void updateBackground();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        Options options_;
        sf::Font* font_;
        sf::RectangleShape background_;
        sf::Color backgroundColor_;
        sf::Color foregroundColor_;
        sf::Color selectColor_;
        std::size_t characterSize_;
        std::size_t lineSpacing_;
        std::size_t width_;
        std::array<std::size_t, static_cast<int>(Padding::SIZE)> padding_;
        int selected_{0};
        std::vector<sf::Text> textArray_;
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_GAMEMENU_HPP_ */
