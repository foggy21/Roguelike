#pragma once
#include "SFML/Graphics.hpp"
#include "Position.h"

class Knight;
class MeleeMob;
class Wizard;

class GameObject {
public:
    GameObject(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void render(sf::RenderWindow& window); // It will need, when I display sprites.
    Position getPosition();
    int getHealth();
    int getDamage();
    void hit(const int& damage);
    void changeDamage(const int& newDamage); // When player will take sword, he changes damage.

    // virtual methods.
    virtual void move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map) = 0;
    virtual bool collide(GameObject& object) = 0;
    virtual bool collide(Knight& knight) = 0;
    virtual bool collide(MeleeMob& mob) = 0;
    virtual bool collide(Wizard& magician) = 0;
protected:
    Position position;
    int health, maxHealth, damage;
private:
    std::shared_ptr<sf::Sprite> sprite;
};