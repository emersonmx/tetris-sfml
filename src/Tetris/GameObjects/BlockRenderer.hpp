#ifndef TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_
#define TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_

#include <SFML/Graphics/RenderTarget.hpp>

#include "Tetris/Game/Tetromino.hpp"
#include "Tetris/Game/Tetris.hpp"
#include "Tetris/GameObjects/GameObject.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {

class BlockRenderer : public GameObject {
    public:
        void create(Assets& assets);

        void tetrominoUpdated(const Tetromino& tetromino);
        void worldUpdated(const Tetris::WorldBlockArray& blocks);

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::array<sf::Color, static_cast<int>(Tetromino::Type::SIZE)> colors_;

        std::array<tetris::Sprite, Tetromino::BLOCK_SIZE> currentTetromino_{};
        std::array<tetris::Sprite, Tetris::WORLD_WIDTH * Tetris::WORLD_HEIGHT> blockSprites_{};

        sf::Transformable transformable_{};
};

} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_BLOCKRENDERER_HPP_ */
