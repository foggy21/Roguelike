#include "Knight.h"

Knight::Knight(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void Knight::move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map)
{
    Position targetPosition = position + offset;
    bool collided = false;

    for (int i = 0; i < objects.size(); ++i) {
        if (targetPosition == objects[i]->getPosition())
            if (!objects[i]->collide(*this)) {
                collided = true;
            }
    }

    if (!collided && map[targetPosition.y][targetPosition.x] == '.')
        position = targetPosition;
}

void Knight::setHealth(int restoredHealth) {
    health += restoredHealth;
    health = health > maxHealth ? maxHealth : health;
}

bool Knight::collide(GameObject& object) {
    return object.collide(*this);
}

bool Knight::collide(Knight& knight) {
    return false;
}

// TODO: Hit Mob and Wizard