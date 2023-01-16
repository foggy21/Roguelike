#pragma once
#include "Thing.h"

class Dagger : public Thing {
public:
    Dagger(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& damage);
    bool collide(Knight& knight) override;
private:
    int damage;
};