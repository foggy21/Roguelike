#pragma once
#include "GameObject.h"
#include <memory>
#include <vector>
#include <string>

class Map {
public:
    Map(const std::string& mapFile);
    void render(sf::RenderWindow& window);
    std::vector<std::shared_ptr<GameObject>>& getEntites();
    std::vector<std::string>& getMap();
private:
    std::vector<std::shared_ptr<GameObject>> entities;
    std::vector<std::string> map;
    sf::Texture tileSet;
    std::shared_ptr<sf::Sprite> grass, wall;
    std::shared_ptr<GameObject> player;
};