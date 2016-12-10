#include "Tetris/GameObjects/RandomMiniBlocks.hpp"

#include <random>

#include "Tetris/Game/Tetromino.hpp"

namespace tetris {
namespace gameobjects {

const char* RandomMiniBlocks::BLOCK_POSITIONS =
"####################################"
"####################################"
"####################################"
"####################################"
"#####     #   #     #   # ##  ######"
"####### ### ##### ### # # # ########"
"####### ###  #### ###  ## ## #######"
"####### ### ##### ### # # ### ######"
"####### ###   ### ### # # #  #######"
"####################################"
"####################################"
"####################################"
"####################################"
"####################################"
"####################################"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"###                              ###"
"####################################"
"####################################"
"####################################";

void RandomMiniBlocks::create(const sf::Texture& blockTexture) {
    const int width = App::WINDOW_WIDTH / HALF_TILE_SIZE;
    const int height = App::WINDOW_HEIGHT / HALF_TILE_SIZE;
    blockSprites_.resize(width * height);

    std::mt19937 rng;
    std::uniform_int_distribution<> uniform_dist(0,
            static_cast<int>(tetris::game::Tetromino::Type::SIZE) - 1);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = i * width + j;
            int colorIndex = uniform_dist(rng);
            auto& block = blockSprites_[index];
            if (BLOCK_POSITIONS[index] == '#') {
                block.setTexture(blockTexture);
                block.setColor(colors_[colorIndex]);
                block.setPosition({j * HALF_TILE_SIZE, i * HALF_TILE_SIZE});
            }
        }
    }
}

} /* namespace gameobjects */
} /* namespace tetris */
