#pragma once
#include "GameObject.h"
#include "Position.h"

class Wizard : public GameObject {
public:
    Wizard(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& entities, const std::vector<std::string> map) override;
    void shoot(const Position& pos, std::vector<std::shared_ptr<GameObject>>& entities, const std::vector<std::string> map);
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(MeleeMob& mob) override;
    bool collide(Wizard& wizard) override;
    bool collide(ThrowingAxe& axe) override;
private:
    // variables for shooting.
    int currentTimeShoot;
    int distanceShoot;
    int timeShoot;
};