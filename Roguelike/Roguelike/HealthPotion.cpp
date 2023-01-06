#include "HealthPotion.h"
#include "Knight.h"

HealthPotion::HealthPotion(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& restoredHealth) : Thing(position, sprite), restoredHealth(restoredHealth) {}

bool HealthPotion::collide(Knight& knight) {
    knight.setHealth(restoredHealth);
    return Thing::collide(knight);
}