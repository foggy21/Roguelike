#include "GameLoop.h"
#include "Settings.h"
#include "Knight.h"
#include <iostream>

GameLoop::GameLoop(const sf::VideoMode& videoMode, const std::string& windowName, const std::string& mapTxt) : map(mapTxt)
{
    window.create(videoMode, windowName, sf::Style::Close);
}

std::string GameLoop::getStatistic(GameObject* gameObject) {
    return "Damage: " + std::to_string(gameObject->getDamage()) + " | " + "Health: " + std::to_string(gameObject->getHealth());
}

WindowState GameLoop::startGame() {
    Settings& settings = Settings::Instance();
    GameState gameState = GameState::Game;

    std::vector<std::string> mapVector = map.getMap();
    auto entities = map.getEntites();
    Knight* player = dynamic_cast<Knight*>(entities[0].get());

    auto windowSize = window.getSize();
    int mapWidth = mapVector[0].length() * settings.sizeOfSprites; // For good screen size in width
    int mapHeight = mapVector.size() * settings.sizeOfSprites; // For good screen size in height

    // From sfml
    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    sf::View ui;
    ui.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

    // Knight's statistic
    sf::Font font;
    font.loadFromFile(settings.pathForFont);
    sf::Text healthText("", font, 16);
    healthText.setPosition(windowSize.x/2, 0);
    healthText.setString(getStatistic(player));

    sf::Text endText("", font, 100);

    auto playerPosition = player->getPosition();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return WindowState::Close;
            }

            if (gameState == GameState::Lose) {
                window.close();
                return WindowState::Restart;
            }

            Position offset = { 0, 0 };
            bool isMove = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                offset = Position{ -1, 0 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                offset = Position{ 1, 0 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                offset = Position{ 0, -1 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                offset = Position{ 0, 1 };
                isMove = true;
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::W) {
                    player->throwDagger(entities, mapVector, 0, -1);
                }
                else if (event.key.code == sf::Keyboard::S) {
                    player->throwDagger(entities, mapVector, 0, 1);
                }
                else if (event.key.code == sf::Keyboard::A) {
                    player->throwDagger(entities, mapVector, -1, 0);
                }
                else if (event.key.code == sf::Keyboard::D) {
                    player->throwDagger(entities, mapVector, 1, 0);
                }
            }

            if (isMove) {
                //Player movement
                player->move(offset, entities, mapVector);
                playerPosition = player->getPosition();

                //Entites movement
                for (int i = 1; i < entities.size(); ++i) {
                    entities[i]->move(playerPosition, entities, mapVector);
                }

                //New statistic
                healthText.setString(getStatistic(player));

                if (player->getHealth() <= 0) {
                    gameState = GameState::Lose;
                    endText.setString("DEAD");
                }
            }

            //Kill entities
            for (int i = 0; i < entities.size(); ++i) {
                if (entities[i]->getHealth() <= 0) {
                    entities.erase(entities.begin() + i);
                    continue;
                }
            }
        }

        int camX = playerPosition.x * settings.sizeOfSprites;
        int camY = playerPosition.y * settings.sizeOfSprites;
        auto cameraSize = camera.getSize();
        
        //Camera offset, from sfml
        if (camX - cameraSize.x / 2 < 0)
            camX = cameraSize.x / 2;
        else if (camX + cameraSize.x / 2 > mapWidth)
            camX = mapWidth - cameraSize.x / 2;

        if (camY - cameraSize.y / 2 < 0)
            camY = cameraSize.y / 2;
        else if (camY + cameraSize.y / 2 > mapHeight)
            camY = mapHeight - cameraSize.y / 2;

        camera.setCenter(camX, camY);
        window.setView(camera);

        window.clear(sf::Color::Black); // Clear map aboard

        window.setView(camera);

        map.render(window);
        // Render entities
        for (int i = 0; i < entities.size(); ++i)
            entities[i]->render(window);

        window.setView(ui);
        window.draw(healthText);
        if (gameState == GameState::Lose) {
            auto bounds = endText.getLocalBounds();
            endText.setPosition(windowSize.x / 2 - bounds.width / 2, windowSize.y / 2 - bounds.height / 2);
            window.draw(endText);
        }

        window.display();

        if (gameState == GameState::Lose)
            sf::sleep(sf::seconds(1));
    }
}