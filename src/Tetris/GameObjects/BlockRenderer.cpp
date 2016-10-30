#include "Tetris/GameObjects/BlockRenderer.hpp"

namespace tetris {
namespace gameobjects {

void BlockRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (auto& block : blockSprites_) {
        if (block.getActive()) {
            target.draw(block, states);
        }
    }
}

} /* namespace gameobjects */
} /* namespace tetris */
