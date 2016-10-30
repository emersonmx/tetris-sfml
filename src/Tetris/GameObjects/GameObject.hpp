#ifndef TETRIS_GAMEOBJECTS_GAMEOBJECT_HPP_
#define TETRIS_GAMEOBJECTS_GAMEOBJECT_HPP_

#include <SFML/Graphics/Sprite.hpp>

namespace tetris {
namespace gameobjects {

class GameObject : public sf::Sprite {
    public:
        virtual ~GameObject() {}

        bool getActive() const { return active_; }
        void setActive(const bool active) { active_ = active; }

    private:
        bool active_{true};
};

} /* namespace gameobjects */
} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_GAMEOBJECT_HPP_ */
