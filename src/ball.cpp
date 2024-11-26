#include <lib/Ball.h>
#include <lib/Constants.h>
#include <raylib.h>

Ball::Ball() :x(0.0f),y(0.0f), radius(18.0f), speed_x(10.0f), speed_y(10.0f) {
    ResetBall();
}

void Ball::Draw() {
    DrawCircle(x, y, radius, YELLOW);
}

void Ball::Update() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        speed_y *= -1;
    }

    if (x + radius >= GetScreenWidth()) {
        player1_score++;
        ResetBall();
    }

    if (x - radius <= 0) {
        player2_score++;
        ResetBall();
    }
}

void Ball::ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    int speed_choices[2] = { -1, 1 };
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
}