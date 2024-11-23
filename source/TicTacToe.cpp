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
    const auto draw_start_button = [&](const Color c)
    {
        DrawRectangleRounded(start_button, 0.6f, 20, c);
        DrawTextEx(game_font, "START", {start_button.x + 20, start_button.y + 10}, 80, 10, GREEN);
    };

    const auto draw_exit_button = [&](const Color c)
    {
        DrawRectangleRounded(exit_button, 0.6f, 20, c);
        DrawTextEx(game_font, "EXIT", {exit_button.x + 70, exit_button.y + 10}, 80, 10, RED);
    };

    draw_start_button(text_color);
    draw_exit_button(text_color);


    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, start_button))
    {
        draw_start_button(hover);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           status = Status::GAME_MENU;
        }
    }

    if (CheckCollisionPointRec(mousePoint, exit_button))
    {
        draw_exit_button(hover);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            status = Status::GAME_CLOSED;
           
        }
    }
}

void qlm::TicTacToe::DrawGameMenu()
{
     // Define button dimensions and positions
    const int button_width = 320;
    const int button_height = 90;

    // Calculate button positions (side by side)
    Rectangle x_button = {
        width / 2 - button_width - 20, // Left button (X) is shifted left
        250,                          // Y position (aligned)
        button_width,
        button_height
    };

    Rectangle o_button = {
        width / 2 + 20, // Right button (O) is shifted right
        250,            // Y position (aligned)
        button_width,
        button_height
    };

    // Draw buttons
    const auto draw_x_button = [&](const Color c)
    {
        DrawRectangleRounded(x_button, 0.6f, 20, c);
        DrawTextEx(game_font, "X", {x_button.x + 130, x_button.y + 15}, 80, 10, GREEN);
    };

    const auto draw_o_button = [&](const Color c)
    {
        DrawRectangleRounded(o_button, 0.6f, 20, c);
        DrawTextEx(game_font, "O", {o_button.x + 130, o_button.y + 10}, 80, 10, RED);
    };

    // Draw the initial buttons
    draw_x_button(text_color);
    draw_o_button(text_color);

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover and handle clicks
    if (CheckCollisionPointRec(mousePoint, x_button))
    {
        draw_x_button(hover);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            player_choice = Cell::X;
            status = Status::GAME_RUNNING;
        }
    }

    if (CheckCollisionPointRec(mousePoint, o_button))
    {
        draw_o_button(hover);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            player_choice = Cell::O;
            status = Status::GAME_RUNNING;
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
            DrawTextEx(game_font, "XO GAME", {width / 2 - 200, 20}, 80, 10, text_color);

            if (status == Status::START_MENU)
            {  
                DrawStartMenu();
            }
            else if (status == Status::GAME_MENU)
            {
                DrawGameMenu();
            }
            else if (status == Status::GAME_RUNNING)
            {

            }
            else if (status == Status::GAME_END)
            {

            }
            else 
            {
               CloseWindow();
            }
        EndDrawing();
    }
}