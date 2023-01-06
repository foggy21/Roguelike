#include "Thing.h"

Thing::Thing(const Position& position, const std::shared_ptr<sf::Sprite> sprite) : GameObject(position, sprite, 1, 0) {}

void Thing::move(const Position& offset, std::vector<std::shared_ptr<GameObject>>& entities, const std::vector<std::string> map) {}

bool Thing::collide(GameObject& object) {
    return object.collide(*this);
}

bool Thing::collide(Knight& knight) {
    health = 0;
    return true;
}

// Same that in H file.