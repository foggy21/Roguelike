#include "GameLoop.h"
#include "Settings.h"

int main() {
    Settings& settings = Settings::Instance();
    settings.loadConfig("../res/settings.json");

    while (true) {
        GameLoop game(sf::VideoMode(settings.width, settings.height),
            settings.gameName, settings.pathForMap);
        if (game.startGame() == WindowState::Close)
            break;
    }
    return 0;
}