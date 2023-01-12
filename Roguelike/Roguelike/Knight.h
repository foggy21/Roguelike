#pragma once
#include "GameObject.h"
#include "Position.h"

class Knight : public GameObject {
public:
    Knight(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map) override;
    void setHealth(int healSize);
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(MeleeMob& mob) override;
    bool collide(Wizard& magician) override;
};