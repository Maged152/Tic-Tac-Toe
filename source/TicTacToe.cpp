#include "TicTacToe.hpp"

qlm::TicTacToe::~TicTacToe()
{
    UnloadFont(game_font);
    CloseWindow();
}

void qlm::TicTacToe::InitTextures()
{
    game_font = LoadFont("resources/orange juice 2.0.ttf");
}

void qlm::TicTacToe::DrawStartMenu()
{
    // Define button dimensions and positions
    const int button_width = 320;
    const int button_height = 90;

    // Calculate button positions
    Rectangle start_button = {
        width / 2 - 170,
        170, 
        button_width,
        button_height
    };

    Rectangle exit_button = {
        width / 2 - 170,
        330,
        button_width,
        button_height
    };


    // Draw buttons
    DrawRectangleRounded(start_button, 0.6f, 20, text_color);
    DrawRectangleRounded(exit_button, 0.6f, 20, text_color);

    // Draw button text
    DrawTextEx(game_font, "START", {start_button.x + 20, start_button.y + 10}, 80, 10, GREEN);
    DrawTextEx(game_font, "EXIT", {exit_button.x + 70, exit_button.y + 10}, 80, 10, RED);

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, start_button))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Add logic to start the game
            DrawText("Start Button Clicked", width / 2 - 120, height - 50, 20, GREEN);
        }
    }

    if (CheckCollisionPointRec(mousePoint, exit_button))
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Add logic to exit the game
           
        }
    }
}

void qlm::TicTacToe::Start(int fps, const char *name)
{
    InitWindow(width, height, name);
    SetTargetFPS(fps);

    InitTextures();

    // game loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(back_ground);

            if (status == Status::START_MENU)
            {
                // Draw title
                DrawTextEx(game_font, "XO GAME", {width / 2 - 200, 20}, 80, 10, text_color);
                DrawStartMenu();
            }
            else if (status == Status::GAME_RUNNING)
            {

            }
            else 
            {
               
            }
        EndDrawing();
    }
}