#pragma once

class Object {
public:
    virtual ~Object() = default;
    virtual void setPosition();
    virtual void setHealth();
    virtual float getDemage();
    //...
};

/*
class Player: public Object;
class Enemy: public Object;
class Boss: public Enemy;
...
*/