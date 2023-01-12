#pragma once

// Position of entities
class Position {
public:
    int x, y;
    friend const Position operator+(const Position& left, const Position& right);
    friend bool operator==(const Position& left, const Position& right);
    friend bool operator!=(const Position& left, const Position& right);
};