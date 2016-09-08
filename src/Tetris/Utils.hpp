#ifndef TETRIS_UTILS_HPP_
#define TETRIS_UTILS_HPP_

#include <SFML/Graphics/Transformable.hpp>

namespace tetris {

namespace Utils {

sf::Vector2f calculateCenterOfRect(const sf::FloatRect& rect);
sf::Vector2f calculateSizeOfRect(const sf::FloatRect& rect);

} /* namespace Utils */

} /* namespace tetris */
#endif /* TETRIS_UTILS_HPP_ */
