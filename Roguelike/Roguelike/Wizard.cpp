#include "Wizard.h"
#include "Knight.h"
#include <cmath>
#include <iostream>

Wizard::Wizard(const Position& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage), currentTimeShoot(0) {}

void Wizard::move(const Position& pos, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map)
{
    // Distance between two points.
    int distance = (int)sqrt(pow(pos.x - position.x, 2) + pow(pos.y - position.y, 2));

    if (distance <= distanceShoot) {
        shoot(pos, objects, map);
    } else {
        Position offsets[] = { Position{1, 0}, Position{-1, 0}, Position{0, 1}, Position{0, -1} };
        // Randomize moving
        srand(time(0));
        int index = rand() % 4;
        Position targetPosition = position + offsets[index];

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
    }
    std::cout << "Wizard Move\n";
}

void Wizard::shoot(const Position& pos, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map) {
    distanceShoot = 5;
    timeShoot = 5;
    // Distance between two points.
    int distance = (int)sqrt(pow(pos.x - position.x, 2) + pow(pos.y - position.y, 2));
    if (distance <= distanceShoot && currentTimeShoot == 0) {
        currentTimeShoot = timeShoot;
        //Do damage!
    }
    else if (distance > distanceShoot) {
        currentTimeShoot = 0;
        move(pos, objects, map); // ???
    }
    else {
        --currentTimeShoot;
    }
}

bool Wizard::collide(GameObject& object) {
    return object.collide(*this);
}

bool Wizard::collide(Knight& knight) {
    health -= knight.getDamage();
    return true;
}

bool Wizard::collide(MeleeMob& mob) {
    return false;
}

bool Wizard::collide(Wizard& magician) {
    return false;
}