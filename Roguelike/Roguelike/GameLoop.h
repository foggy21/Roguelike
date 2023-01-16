#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "GameObject.h"
#include <string>

enum class GameState { Game, Lose };
enum class WindowState { Close, Restart };

class GameLoop {
public:
    GameLoop(const sf::VideoMode& videoMode, const std::string& windowName, const std::string& startMapFile);
    WindowState startGame();
private:
    sf::RenderWindow window;
    Map map;
    std::vector<std::shared_ptr<GameObject>> objects;
    std::string getStatistic(GameObject* gameObject);
};