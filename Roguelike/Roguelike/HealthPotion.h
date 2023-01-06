#pragma once
#include "Thing.h"

class HealthPotion : public Thing {
public:
    HealthPotion(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& restoredHealth);
    bool collide(Knight& knight) override;
private:
    int restoredHealth;
};