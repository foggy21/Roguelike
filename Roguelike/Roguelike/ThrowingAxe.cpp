#include "ThrowingAxe.h"
#include "Knight.h"
#include "MeleeMob.h"

ThrowingAxe::ThrowingAxe(const Position& position, const int& damage, const int& move_x, const int& move_y) : GameObject(position, ThrowingAxe::staticSprite, 1, damage), move_x(move_x), move_y(move_y) {}

void ThrowingAxe::setSprite(const std::shared_ptr<sf::Sprite> sprite) {
    staticSprite = sprite;
}

void ThrowingAxe::move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& entities,
    const std::vector<std::string> map)
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

bool ThrowingAxe::collide(GameObject& object) {
    return object.collide(*this);
}

bool ThrowingAxe::collide(Knight& knight) {
    knight.hit(damage);
    health = 0;
    return false;
}

bool ThrowingAxe::collide(MeleeMob& mob) {
    mob.hit(damage);
    health = 0;
    return false;
}

bool ThrowingAxe::collide(Wizard& wizard) {
    return false;
}

bool ThrowingAxe::collide(ThrowingAxe& fireball) {
    health = 0;
    return false;
}