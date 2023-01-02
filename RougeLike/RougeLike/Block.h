#pragma once

class Block {
public:
    virtual ~Block() = default;
    virtual void setPosition(...);
    //...
};

/*
class Wall: public Block;
class Grass: public Block;
class Bomb: public Block;
class Spawner: public Block;
class Weapon: public Block;
class Sword: public Weapon;
...
*/