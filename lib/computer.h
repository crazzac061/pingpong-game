#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"

class ComputerOpponent : public Player
{
private:
    float targetY;
    float currentSpeed;

public:
    ComputerOpponent();
    void Update(Ball& ball) override;
};

#endif 