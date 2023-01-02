#pragma once

class Game {
    std::vector<std::unique_ptr<Object>> objects;
    std::vector<std::unique_ptr<Block>> objects;

    Render render;
    Collider collider;
public:
    void input();
    void update();
    void draw();
};
