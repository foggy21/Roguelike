#pragma once
#include "GameObject.h"

class Knight : public GameObject {
public:
    Knight(const Position& position, const std::shared_ptr<sf::Sprite> sprite,
        const int& health, const int& damage);
    void move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& objects,
        const std::vector<std::string> map) override;
    void setHealth(int healSize);
    void castFireball(std::vector<std::shared_ptr<GameObject>>& objects,
        const std::vector<std::string> map, const int& dx, const int& dy);
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(MeleeMob& mob) override;
    bool collide(Wizard& magician) override;
};