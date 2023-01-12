#include "Dagger.h"
#include "Knight.h"
#include "Position.h"

Dagger::Dagger(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& damage) : Thing(position, sprite), damage(damage) {}

bool Dagger::collide(Knight& knight) {
    knight.changeDamage(damage);
    return Thing::collide(knight);
}