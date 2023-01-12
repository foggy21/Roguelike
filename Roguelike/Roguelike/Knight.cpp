#include "Knight.h"
#include "MeleeMob.h"
#include "Wizard.h"

Knight::Knight(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void Knight::move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& entities, const std::vector<std::string> map)
{
    Position targetPosition = position + pos;
    bool collided = false;

    //Check collide with different objects.
    for (int i = 0; i < entities.size(); ++i) {
        if (targetPosition == entities[i]->getPosition()) {
            if (!entities[i]->collide(*this)) {
                collided = true;
            }
        }
    }

    // Don't collide with object and targetPos - grass.
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

bool Knight::collide(MeleeMob& mob) {
    health -= mob.getDamage();
    return false;
}

bool Knight::collide(Wizard& wizard) {
    health -= wizard.getDamage();
    return false;
}

bool Knight::collide(Knight& knight) {
    return false;
}