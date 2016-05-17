#ifndef TETRIS_GAMEOBJECTS_GAMEOBJECT_HPP_
#define TETRIS_GAMEOBJECTS_GAMEOBJECT_HPP_

#include <SFML/Graphics/Drawable.hpp>

namespace tetris {

class GameObject : public sf::Drawable {
    public:
        virtual ~GameObject() {}

        bool active() { return active_; }
        void setActive(bool active) { active_ = active; }

        virtual void create() {}
        virtual void destroy() {}

        virtual void update() {}

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

    private:
        bool active_ = true;
};

} /* namespace tetris */
#endif /* TETRIS_GAMEOBJECTS_GAMEOBJECT_HPP_ */
