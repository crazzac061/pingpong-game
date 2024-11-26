#include <lib/HumanPlayer.h>
#include <raylib.h>

HumanPlayer::HumanPlayer(int up, int down) : up_key(up), down_key(down) {}

void HumanPlayer::Update(Ball& ball) {
    if (IsKeyDown(up_key)) {
        y -= speed;
    }
    if (IsKeyDown(down_key)) {
        y += speed;
    }
    LimitMovement();
}