#pragma once
#include "GameObject.h"
#include "Position.h"

class Thing : public GameObject {
public:
    Thing(const Position& position, const std::shared_ptr<sf::Sprite> sprite);
    void move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& entites, const std::vector<std::string> map) override;
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(MeleeMob& mob) override;
    bool collide(Wizard& wizard) override;
    bool collide(ThrowingAxe& axe) override;
};