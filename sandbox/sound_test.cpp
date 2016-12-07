#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Audio Test");
    sf::SoundBuffer buffer;
    buffer.loadFromFile("../assets/game_start.wav");
    sf::Sound sound(buffer);
    sound.play();

    bool running = true;
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }

        window.clear();
        window.display();
    }
    return 0;
}
