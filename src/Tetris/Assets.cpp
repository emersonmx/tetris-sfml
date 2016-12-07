#include "Tetris/Assets.hpp"

#include <iostream>

namespace tetris {

sf::Sound& Assets::getEraseLinesSound() {
    return sounds_[static_cast<int>(SoundID::ERASE_LINES)];
}

sf::Sound& Assets::getFitTetrominoSound() {
    return sounds_[static_cast<int>(SoundID::FIT_TETROMINO)];
}

sf::Sound& Assets::getGameOverSound() {
    return sounds_[static_cast<int>(SoundID::GAME_OVER)];
}

sf::Sound& Assets::getGameStartSound() {
    return sounds_[static_cast<int>(SoundID::GAME_START)];
}

sf::Sound& Assets::getMenuOpenSound() {
    return sounds_[static_cast<int>(SoundID::MENU_OPEN)];
}

sf::Sound& Assets::getMoveTetrominoSound() {
    return sounds_[static_cast<int>(SoundID::MOVE_TETROMINO)];
}

sf::Sound& Assets::getRotateTetrominoSound() {
    return sounds_[static_cast<int>(SoundID::ROTATE_TETROMINO)];
}

void Assets::loadAssets() {
    block_ = loadFromFile<sf::Texture>("assets/block.png");
    grid_ = loadFromFile<sf::Texture>("assets/grid.png");
    mainMenuTexture_ = loadFromFile<sf::Texture>("assets/main_menu.jpg");

    defaultFont_ = loadFromFile<sf::Font>("assets/Chewy.ttf");

    loadSounds();
}

void Assets::loadSounds() {
    mainMusic_ = openMusicFromFile("assets/main_music.ogg");

    soundBuffers_[static_cast<int>(SoundID::ERASE_LINES)] =
        loadFromFile<sf::SoundBuffer>("assets/erase_lines.wav");
    soundBuffers_[static_cast<int>(SoundID::FIT_TETROMINO)] =
        loadFromFile<sf::SoundBuffer>("assets/fit_tetromino.wav");
    soundBuffers_[static_cast<int>(SoundID::GAME_OVER)] =
        loadFromFile<sf::SoundBuffer>("assets/game_over.wav");
    soundBuffers_[static_cast<int>(SoundID::GAME_START)] =
        loadFromFile<sf::SoundBuffer>("assets/game_start.wav");
    soundBuffers_[static_cast<int>(SoundID::MENU_OPEN)] =
        loadFromFile<sf::SoundBuffer>("assets/menu_open.wav");
    soundBuffers_[static_cast<int>(SoundID::MOVE_TETROMINO)] =
        loadFromFile<sf::SoundBuffer>("assets/move_tetromino.wav");
    soundBuffers_[static_cast<int>(SoundID::ROTATE_TETROMINO)] =
        loadFromFile<sf::SoundBuffer>("assets/rotate_tetromino.wav");

    std::size_t soundSize = soundBuffers_.size();
    for (std::size_t i = 0; i < soundSize; ++i) {
        auto& buffer = soundBuffers_[i];
        sounds_[i].setBuffer(buffer);
    }
}

template<class T>
T Assets::loadFromFile(const std::string& filename) {
    T resource;
    if (!resource.loadFromFile(filename)) {
        std::cout << "Couldn't load \"" << filename << "\"\n";
    }

    return resource;
}

Assets::MusicPtr Assets::openMusicFromFile(const std::string& filename) {
    std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filename)) {
        std::cout << "Couldn't load \"" << filename << "\"\n";
    }

    return music;
}

} /* namespace tetris */
