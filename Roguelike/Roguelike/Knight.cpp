#include "Knight.h"
#include "MeleeMob.h"
#include "ThrowingAxe.h"
#include "ThrowingDagger.h"
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

void Knight::throwDagger(std::vector<std::shared_ptr<GameObject>>& entities, const std::vector<std::string> map, const int& move_x, const int& move_y)
{
    entities.push_back(std::make_shared<ThrowingDagger>(position, 35, move_x, move_y));
    entities.back()->move(Position{ move_x, move_y }, entities, map);
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

bool Knight::collide(ThrowingAxe& axe) {
    health -= axe.getDamage();
    return true;
}

bool Knight::collide(ThrowingDagger& dagger) {
    return false;
}