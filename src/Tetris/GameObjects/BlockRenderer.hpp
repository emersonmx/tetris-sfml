#ifndef TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_
#define TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_

#include <SFML/Graphics/RenderTarget.hpp>

#include "Tetris/Game/Tetromino.hpp"
#include "Tetris/Game/Tetris.hpp"
#include "Tetris/GameObjects/GameObject.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {
namespace gameobjects {

class BlockRenderer : public GameObject {
    public:
        void create(Assets& assets);

        void tetrominoUpdated(const tetris::game::Tetromino& tetromino);
        void worldUpdated(const tetris::game::Tetris::WorldBlockArray& blocks);

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::array<sf::Color, static_cast<int>(tetris::game::Tetromino::Type::SIZE)> colors_;

        std::array<GameObject, tetris::game::Tetromino::BLOCK_SIZE> currentTetromino_{};
        std::array<GameObject, tetris::game::Tetris::WORLD_WIDTH * tetris::game::Tetris::WORLD_HEIGHT> blockSprites_{};
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_ */
