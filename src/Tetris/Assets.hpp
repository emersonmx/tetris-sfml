#ifndef TETRIS_ASSETS_HPP_
#define TETRIS_ASSETS_HPP_

#include <memory>
#include <array>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

namespace tetris {

class Assets {
    public:
        virtual ~Assets() {}

        sf::Texture& getBlock() { return block_; }
        sf::Texture& getMiniBlockTexture() { return miniBlockTexture_; }
        sf::Texture& getGrid() { return grid_; }
        sf::Texture& getMainMenuBackgroundTexture() { return mainMenuBackgroundTexture_; }

        sf::Font& getDefaultFont() { return defaultFont_; }

        sf::Music& getMainMusic() { return *mainMusic_; }
        sf::Sound& getEraseLinesSound();
        sf::Sound& getFitTetrominoSound();
        sf::Sound& getGameOverSound();
        sf::Sound& getGameStartSound();
        sf::Sound& getMenuOpenSound();
        sf::Sound& getMoveTetrominoSound();
        sf::Sound& getRotateTetrominoSound();

        void loadAssets();

    private:
        enum class SoundID {
            ERASE_LINES, FIT_TETROMINO, GAME_OVER, GAME_START,
            MENU_OPEN, MOVE_TETROMINO, ROTATE_TETROMINO, SIZE
        };

        using MusicPtr = std::unique_ptr<sf::Music>;

        void loadSounds();

        template<class T>
        T loadFromFile(const std::string& filename);
        MusicPtr openMusicFromFile(const std::string& filename);


        sf::Texture block_;
        sf::Texture miniBlockTexture_;
        sf::Texture grid_;
        sf::Texture mainMenuBackgroundTexture_;

        sf::Font defaultFont_;

        MusicPtr mainMusic_;

        std::array<sf::Sound, static_cast<int>(SoundID::SIZE)> sounds_{};
        std::array<sf::SoundBuffer, static_cast<int>(SoundID::SIZE)> soundBuffers_{};
};

} /* namespace tetris */
#endif /* TETRIS_ASSETS_HPP_ */
