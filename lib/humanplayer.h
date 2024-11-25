#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
private:
    int up_key;
    int down_key;

public:
    HumanPlayer(int up, int down);
    void Update(Ball& ball) override;
};

#endif // HUMANPLAYER_H