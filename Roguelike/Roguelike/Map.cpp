#include "Map.h"
#include "Settings.h"
#include "Knight.h"
#include "MeleeMob.h"
#include "Wizard.h"
#include "HealthPotion.h"
#include "Dagger.h"
#include <fstream>

Map::Map(const std::string& mapFile) {
    Settings& settings = Settings::Instance();
    std::ifstream file(settings.pathForMap);

    // Get map from txt
    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        map.push_back(line);
    }
    file.close();

    tileSet.loadFromFile(settings.pathForTilemap);

    //Get sprites
    grass = std::make_shared<sf::Sprite>(tileSet);
    grass->setTextureRect(sf::IntRect(0, 0, settings.sizeOfSprites, settings.sizeOfSprites));

    wall = std::make_shared<sf::Sprite>(tileSet);
    wall->setTextureRect(sf::IntRect(68, 50, settings.sizeOfSprites, settings.sizeOfSprites));

    auto spriteKnight = std::make_shared<sf::Sprite>(tileSet);
    spriteKnight->setTextureRect(sf::IntRect(0, 138, settings.sizeOfSprites, settings.sizeOfSprites));

    auto spriteMob = std::make_shared<sf::Sprite>(tileSet);
    spriteMob->setTextureRect(sf::IntRect(0, 154, settings.sizeOfSprites, settings.sizeOfSprites));

    auto spriteHealth = std::make_shared<sf::Sprite>(tileSet);
    spriteHealth->setTextureRect(sf::IntRect(123, 154, settings.sizeOfSprites, settings.sizeOfSprites));

    auto spriteDagger = std::make_shared<sf::Sprite>(tileSet);
    spriteDagger->setTextureRect(sf::IntRect(123, 138, settings.sizeOfSprites, settings.sizeOfSprites));

    auto spriteWizard = std::make_shared<sf::Sprite>(tileSet);
    spriteWizard->setTextureRect(sf::IntRect(0, 121, settings.sizeOfSprites, settings.sizeOfSprites));

    // Set entities
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            bool isObject = false;

            if (map[i][j] == settings.entities["knight"]) {
                player = std::make_shared<Knight>(Position{ j, i }, spriteKnight, 100, 20);
                entities.push_back(player);
                isObject = true;
            }
            else if (map[i][j] == settings.entities["mob"]) {
                entities.push_back(std::make_shared<MeleeMob>(Position{ j, i }, spriteMob, 50, 15));
                isObject = true;
            }
            else if (map[i][j] == settings.entities["wizard"]) {
                entities.push_back(std::make_shared<Wizard>(Position{ j, i }, spriteWizard, 100, 20));
                isObject = true;
            }
            else if (map[i][j] == settings.entities["health"]) {
                entities.push_back(std::make_shared<HealthPotion>(Position{ j, i }, spriteHealth, 40));
                isObject = true;
            }
            else if (map[i][j] == settings.entities["dagger"]) {
                entities.push_back(std::make_shared<Dagger>(Position{ j, i }, spriteDagger, 15));
                isObject = true;
            }

            if (isObject)
                map[i][j] = '.';
        }
    }

    for (int i = 0; i < entities.size(); ++i)
        if (entities[i] == player) {
            entities.erase(entities.begin() + i);
            break;
        }

    entities.insert(entities.begin(), player);
}

void Map::render(sf::RenderWindow& window) {
    Settings& settings = Settings::Instance();

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            if (map[i][j] == settings.entities["grass"]) {
                grass->setPosition(sf::Vector2f(j * settings.sizeOfSprites, i * settings.sizeOfSprites));
                window.draw(*grass);
            }
            else if (map[i][j] == settings.entities["wall"]) {
                wall->setPosition(sf::Vector2f(j * settings.sizeOfSprites, i * settings.sizeOfSprites));
                window.draw(*wall);
            }
        }
    }
}

std::vector<std::shared_ptr<GameObject>>& Map::getEntites() {
    return entities;
}

std::vector<std::string>& Map::getMap() {
    return map;
}