#include "MeleeMob.h"
#include "Knight.h"
#include "ThrowingAxe.h"
#include "ThrowingDagger.h"
#include <cmath>
#include <iostream>

MeleeMob::MeleeMob(const Position& position, const std::shared_ptr<sf::Sprite> sprite,
    const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void MeleeMob::move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map)
{
    int vizableDistance = 7;

    // Distance between two points.
    int distToPlayer = sqrt(pow(pos.x - position.x, 2) + pow(pos.y - position.y, 2));
    Position targetPosition;
    if (distToPlayer <= vizableDistance) {
        int deltaX = pos.x - position.x;
        int deltaY = pos.y - position.y;
        
        // deltas equal 1 or -1 if they're not 0.
        deltaX /= deltaX != 0 ? abs(deltaX) : 1;
        deltaY /= deltaY != 0 ? abs(deltaX) : 1;

        if (deltaX == 0)
            targetPosition = position + Position{ 0, deltaY };
        else if (deltaY == 0)
            targetPosition = position + Position{ deltaX, 0 };
        else {
            // Random move to knight.
            srand(time(0));
            int index = rand() % 2;
            targetPosition = index == 0 ? position + Position{ deltaX, 0 } : position + Position{ 0, deltaY };
        }
    }
    else {
        // Randomize moving.
        Position offsets[] = { Position{1, 0}, Position{-1, 0}, Position{0, 1}, Position{0, -1} };
        int index = rand() % 4;
        targetPosition = position + offsets[index];
    }

    bool collided = false;

    //Check collide with different objects.
    for (int i = 0; i < objects.size(); ++i) {
        if (targetPosition == objects[i]->getPosition())
            if (!objects[i]->collide(*this)) {
                collided = true;
            }
    }

    // Don't collide with object and targetPos - grass.
    if (!collided && map[targetPosition.y][targetPosition.x] == '.')
        position = targetPosition;
    std::cout << "Monster Move\n";
}

bool MeleeMob::collide(GameObject& object) {
    return object.collide(*this);
}

bool MeleeMob::collide(Knight& knight) {
    health -= knight.getDamage();
    return false;
}

bool MeleeMob::collide(MeleeMob& mob) {
    return false;
}

bool MeleeMob::collide(Wizard& wizard) {
    return false;
}

bool MeleeMob::collide(ThrowingAxe& axe) {
    return false;
}

bool MeleeMob::collide(ThrowingDagger& dagger) {
    health -= dagger.getDamage();
    return false;
}