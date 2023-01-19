#pragma once
#include "GameObject.h"

class ThrowingDagger : public GameObject {
public:
    static std::shared_ptr<sf::Sprite> staticSprite;
    ThrowingDagger(const Position& position, const int& damage, const int& dx, const int& dy);
    static void setSprite(const std::shared_ptr<sf::Sprite> sprite);
    void move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map) override;
    bool collide(GameObject& object) override;
    bool collide(Knight& knight) override;
    bool collide(MeleeMob& mob) override;
    bool collide(Wizard& wizard) override;
    bool collide(ThrowingDagger& dagger) override;
    bool collide(ThrowingAxe& axe) override;
private:
    int move_x;
    int move_y;
};