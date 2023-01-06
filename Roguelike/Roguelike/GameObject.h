#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

struct Position {
    int x, y;
    friend const Position operator+(const Position& left, const Position& right);
    friend bool operator==(const Position& left, const Position& right);
    friend bool operator!=(const Position& left, const Position& right);
};

class Knight;
class MeleeMob;
class Wizard;

class GameObject {
public:
    GameObject(const Position& position, const std::shared_ptr<sf::Sprite> sprite,
        const int& health, const int& damage);
    void draw(sf::RenderWindow& window);
    Position getPosition();
    int getHealth();
    int getDamage();
    void hit(const int& damageSize);
    void changeDamage(const int& incSize);
    virtual void move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& objects,
        const std::vector<std::string> map) = 0;
    // true - object can move to this point | false - can't
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