#pragma once
#include "GameObject.h"

class Thing : public GameObject {
public:
    Thing(const Position& position, const std::shared_ptr<sf::Sprite> sprite);
    void move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& entites, const std::vector<std::string> map) override;
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    // TODO: Collide with Wizard and Mob.
};