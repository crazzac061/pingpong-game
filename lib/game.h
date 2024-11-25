#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Player.h"
#include <memory>
#include <string>

class Game
{
private:
    Ball ball;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    bool is_multiplayer;
    bool game_over;
    std::string winner;

    void ResetGame();
    void InitializePlayers(bool is_multiplayer);
    bool ShowMenuScreen();

public:
    Game();
    void Run();
};

#endif // GAME_H