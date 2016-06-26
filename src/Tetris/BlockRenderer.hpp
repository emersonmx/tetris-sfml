#ifndef TETRIS_BLOCKRENDERER_HPP_
#define TETRIS_BLOCKRENDERER_HPP_

#include <array>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Tetris/Defs.hpp"
#include "Tetris/Game/Tetris.hpp"
#include "Tetris/Assets.hpp"

namespace tetris {

class BlockRenderer : public Tetris::Listener, public sf::Drawable {
    public:
        class Sprite : public sf::Sprite {
            public:
                bool active() const { return active_; }
                void setActive(const bool active) { active_ = active; }

            private:
                bool active_{true};
        };

        sf::Vector2f position() { return transformable_.getPosition(); }
        void setPosition(const sf::Vector2f& position) {
            transformable_.setPosition(position);
        }

        void create(Assets& assets);
        void destroy();

        void gameStarted(Tetris& tetris) override;
        void gameOver(Tetris& tetris) override;

        void scoreUpdated(const int score) override;

        void tetrominoUpdated(const Tetromino& tetromino) override;
        void worldUpdated(const Tetris::WorldBlockArray& worldBlockArray) override;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        std::array<sf::Color, static_cast<int>(Tetromino::Type::SIZE)> colors_;

        std::array<Sprite, Tetromino::BLOCK_SIZE> currentTetromino_{};
        std::array<Sprite, Tetris::WORLD_WIDTH * Tetris::WORLD_HEIGHT> blockSprites_{};

        sf::Transformable transformable_{};
};

} /* namespace tetris */
#endif /* TETRIS_BLOCKRENDERER_HPP_ */
