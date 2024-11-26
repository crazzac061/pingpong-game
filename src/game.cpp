#include <lib/Game.h>
#include <lib/HumanPlayer.h>
#include <lib/Computer.h>
#include <lib/Constants.h>
#include <raylib.h>

Game::Game() : is_multiplayer(false), game_over(false) {}

void Game::ResetGame() {
    player1_score = 0;
    player2_score = 0;
    game_over = false;
    winner = "";
    ball.ResetBall();
    player1->y = static_cast<float>(GetScreenHeight()) / 2 - player1->height / 2;
    player2->y = static_cast<float>(GetScreenHeight()) / 2 - player2->height / 2;
}

void Game::InitializePlayers(bool is_multiplayer) {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    player1 = std::make_unique<HumanPlayer>(KEY_W, KEY_S);
    player1->width = 25.0f;
    player1->height = 120.0f;
    player1->x = 10.0f;
    player1->y = static_cast<float>(screen_height) / 2 - player1->height / 2;
    player1->speed = 15.0f;

    if (is_multiplayer) {
        player2 = std::make_unique<HumanPlayer>(KEY_UP, KEY_DOWN);
    }
    else {
        player2 = std::make_unique<ComputerOpponent>();
    }
    player2->width = 25.0f;
    player2->height = 120.0f;
    player2->x = static_cast<float>(screen_width) - player2->width - 10.0f;
    player2->y = static_cast<float>(screen_height) / 2 - player2->height / 2;
    player2->speed = 15.0f;
}

bool Game::ShowMenuScreen() {
    const int screen_width = GetScreenWidth();
    const int screen_height = GetScreenHeight();

    Rectangle multiplayerButton = {
        static_cast<float>(screen_width / 2 - 150),
        static_cast<float>(screen_height / 2 - 60),
        300.0f,
        50.0f
    };
    Rectangle computerButton = {
        static_cast<float>(screen_width / 2 - 150),
        static_cast<float>(screen_height / 2 + 10),
        300.0f,
        50.0f
    };

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(Dark_Green);
        DrawText("PONG", screen_width / 2 - MeasureText("PONG", 60) / 2, 100, 60, WHITE);
        DrawText("Choose Game Mode", screen_width / 2 - MeasureText("Choose Game Mode", 30) / 2, 200, 30, WHITE);

        DrawRectangleRec(multiplayerButton, Light_Green);
        DrawRectangleRec(computerButton, Light_Green);

        DrawText("Multiplayer", static_cast<int>(multiplayerButton.x + 75), static_cast<int>(multiplayerButton.y + 15), 20, WHITE);
        DrawText("Play Against Computer", static_cast<int>(computerButton.x + 40), static_cast<int>(computerButton.y + 15), 20, WHITE);

        EndDrawing();

        if (CheckCollisionPointRec(GetMousePosition(), multiplayerButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            return true;
        }
        if (CheckCollisionPointRec(GetMousePosition(), computerButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            return false;
        }
    }

    return false;  // Default to Computer mode if window is closed
}

void Game::Run() {
    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pong Game");
    SetTargetFPS(60);

    is_multiplayer = ShowMenuScreen();
    InitializePlayers(is_multiplayer);
    ResetGame();

    while (!WindowShouldClose()) {
        BeginDrawing();

        if (!game_over) {
            ball.Update();
            player1->Update(ball);
            player2->Update(ball);

            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
                Rectangle{ player2->x, player2->y, player2->width, player2->height })) {
                ball.speed_x *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
                Rectangle{ player1->x, player1->y, player1->width, player1->height })) {
                ball.speed_x *= -1;
            }

            if (player1_score >= 10) {
                game_over = true;
                winner = "Player 1";
            }
            else if (player2_score >= 10) {
                game_over = true;
                winner = is_multiplayer ? "Player 2" : "Computer";
            }
        }
        else {
            if (IsKeyPressed(KEY_R)) {
                ResetGame();
            }
        }

        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player1->Draw();
        player2->Draw();
        DrawText(TextFormat("%i", player1_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player2_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        if (game_over) {
            DrawRectangle(0, 0, screen_width, screen_height, Color{ 0, 0, 0, 200 });
            DrawText(TextFormat("%s Wins!", winner.c_str()),
                screen_width / 2 - MeasureText(TextFormat("%s Wins!", winner.c_str()), 60) / 2,
                screen_height / 2 - 30, 60, WHITE);
            DrawText("Press R to Restart",
                screen_width / 2 - MeasureText("Press R to Restart", 30) / 2,
                screen_height / 2 + 50, 30, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}