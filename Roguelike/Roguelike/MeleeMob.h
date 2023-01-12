#pragma once
#include "GameObject.h"
#include "Position.h"

class MeleeMob : public GameObject {
public:
    MeleeMob(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& entites, const std::vector<std::string> map) override;
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(MeleeMob& mob) override;
    bool collide(Wizard& wizard) override;
};