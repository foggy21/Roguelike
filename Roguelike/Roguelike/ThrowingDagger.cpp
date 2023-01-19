#include "ThrowingDagger.h"
#include "Wizard.h"
#include "MeleeMob.h"

std::shared_ptr<sf::Sprite> ThrowingDagger::staticSprite;

ThrowingDagger::ThrowingDagger(const Position& position, const int& damage, const int& move_x, const int& move_y) : GameObject(position, ThrowingDagger::staticSprite, 1, damage), move_x(move_x), move_y(move_y) {}

void ThrowingDagger::setSprite(const std::shared_ptr<sf::Sprite> sprite) {
    ThrowingDagger::staticSprite = sprite;
}

void ThrowingDagger::move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& entities, const std::vector<std::string> map)
{
    Position targetPosition = position + Position{ move_x, move_y };
    bool collided = false;

    for (int i = 0; i < entities.size(); ++i) {
        if (targetPosition == entities[i]->getPosition())
            if (!entities[i]->collide(*this)) {
                collided = true;
            }
    }

    if (!collided && map[targetPosition.y][targetPosition.x] == '.')
        position = targetPosition;
    else if (map[targetPosition.y][targetPosition.x] == '#')
        health = 0;
}

bool ThrowingDagger::collide(GameObject& object) {
    return object.collide(*this);
}

bool ThrowingDagger::collide(Knight& knight) {
    health = 0;
    return false;
}

bool ThrowingDagger::collide(MeleeMob& mob) {
    mob.hit(damage);
    health = 0;
    return false;
}

bool ThrowingDagger::collide(Wizard& wizard) {
    wizard.hit(damage);
    health = 0;
    return false;
}

bool ThrowingDagger::collide(ThrowingDagger& dagger) {
    health = 0;
    return false;
}
bool ThrowingDagger::collide(ThrowingAxe& dagger) {
    health = 0;
    return false;
}