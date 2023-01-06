#include "GameObject.h"
#include "Settings.h"

const Position operator+(const Position& left, const Position& right) {
    return Position{ left.x + right.x, left.y + right.y };
}

bool operator==(const Position& left, const Position& right) {
    return left.x == right.x && left.y == right.y;
}

bool operator!=(const Position& left, const Position& right) {
    return left.x != right.x || left.y != right.y;
}

GameObject::GameObject(const Position& position, std::shared_ptr<sf::Sprite> sprite, const int& health,const int& damage) : position(position), sprite(sprite), health(health), maxHealth(health), damage(damage){}

void GameObject::draw(sf::RenderWindow& window) {
    Settings& settings = Settings::Instance();
    sprite->setPosition(sf::Vector2f(position.x * settings.sizeOfSprites,
        position.y * settings.sizeOfSprites));

    window.draw(*sprite);
}

Position GameObject::getPosition() {
    return position;
}

int GameObject::getHealth() {
    return health;
}

int GameObject::getDamage() {
    return damage;
}

void GameObject::hit(const int& damageSize) {
    if (damageSize > 0)
        health -= damageSize;
}

void GameObject::changeDamage(const int& incSize) {
    damage += incSize;
}