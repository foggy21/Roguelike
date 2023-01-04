#include "Knight.h"

Knight::Knight(const Position& position, const std::shared_ptr<sf::Sprite> sprite,
    const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void Knight::move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& objects,
    const std::vector<std::string> map)
{
    Position toPos = position + offset;
    bool wasCollide = false;

    for (int i = 0; i < objects.size(); ++i) {
        if (toPos == objects[i]->getPosition())
            if (!objects[i]->collide(*this)) {
                wasCollide = true;
            }
    }

    if (!wasCollide && map[toPos.y][toPos.x] == '.')
        position = toPos;
}

void Knight::heal(int healSize) {
    health += healSize;
    health = health > maxHealth ? maxHealth : health;
}

bool Knight::collide(GameObject& object) {
    return object.collide(*this);
}

bool Knight::collide(Knight& knight) {
    return false;
}

// TODO: Hit Monster and Wizard