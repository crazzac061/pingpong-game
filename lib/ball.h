
#ifndef BALL_H
#define BALL_H

#include "raylib.h"

class Ball
{
public:
    Ball();
    void Draw();
    void Update();
    void ResetBall();

    float x, y;
    int radius;
    int speed_x, speed_y;

   
};

#endif 