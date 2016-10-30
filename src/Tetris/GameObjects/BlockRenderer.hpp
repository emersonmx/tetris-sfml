#ifndef TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_
#define TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_

#include <array>
#include <vector>

#include <SFML/Graphics/RenderTarget.hpp>

#include "Tetris/GameObjects/GameObject.hpp"
#include "Tetris/Game/Tetromino.hpp"

namespace tetris {
namespace gameobjects {

class BlockRenderer : public GameObject {
    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::array<sf::Color, static_cast<int>(tetris::game::Tetromino::Type::SIZE)>
            colors_ {
                sf::Color(50, 255, 255),
                sf::Color(50, 50, 255),
                sf::Color(255, 123, 50),
                sf::Color(255, 255, 50),
                sf::Color(99, 255, 50),
                sf::Color(99, 50, 99),
                sf::Color(255, 50, 50)
            };

        std::vector<GameObject> blockSprites_{};
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_ */
