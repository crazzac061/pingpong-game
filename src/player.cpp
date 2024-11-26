#include <lib/Player.h>
#include <raylib.h>

void Player::LimitMovement() {
    if (y <= 0) {
        y = 0;
    }
    if (y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;
    }
}

void Player::Draw() {
    DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
}