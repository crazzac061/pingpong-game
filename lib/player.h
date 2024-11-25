#ifndef PLAYER_H
#define PLAYER_H

#include "Ball.h"

class Player
{
protected:
    void LimitMovement();

public:
    float x, y;
    int speed;
    float width, height;

    virtual void Draw();
    virtual void Update(Ball& ball) = 0;
};

#endif // PLAYER_H