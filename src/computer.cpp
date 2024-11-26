#include<lib/Computer.h>
#include <raylib.h>
#include <cmath>

ComputerOpponent::ComputerOpponent() : targetY(0), currentSpeed(0) {}

void ComputerOpponent::Update(Ball& ball) {
    
    float predictedY = ball.y;

    targetY = predictedY + GetRandomValue(-25, 25);

    float distanceToTarget = predictedY - (y + height / 2);

    currentSpeed = speed * (distanceToTarget / 150.0f);

    y += currentSpeed;

    
    LimitMovement();
}