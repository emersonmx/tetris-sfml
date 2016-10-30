#include "Tetris/Utils.hpp"

#include <SFML/Graphics/Rect.hpp>

namespace tetris {
namespace utils {

sf::Vector2f calculateCenterOfRect(const sf::FloatRect& rect) {
    return sf::Vector2f(rect.left + rect.width / 2.0f,
                        rect.top + rect.height / 2.0f);
}

sf::Vector2f calculateSizeOfRect(const sf::FloatRect& rect) {
    return sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
}

} /* namespace utils */
} /* namespace tetris */
