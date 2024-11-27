#include "TicTacToe.hpp"

qlm::TicTacToe::~TicTacToe()
{
    UnloadFont(game_font);
    UnloadFont(grid_font);
    CloseWindow();
}

void qlm::TicTacToe::InitTextures()
{
    game_font = LoadFont("resources/orange juice 2.0.ttf");
    grid_font = LoadFont("resources/Surfing Capital.ttf");
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
           status = Status::GAME_TYPE;
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

void qlm::TicTacToe::DrawGameType()
{
    // Define button dimensions and positions
    const int button_width = 600;
    const int button_height = 110;

    // Calculate button positions
    Rectangle single_button = {
        width / 2 - button_width / 2,
        170, 
        button_width,
        button_height
    };

    Rectangle multi_button = {
        width / 2 - button_width / 2,
        330,
        button_width,
        button_height
    };


    // Draw buttons
    const auto draw_single_button = [&](const Color c)
    {
        DrawRectangleRounded(single_button, 0.6f, 20, c);
        DrawTextEx(game_font, "Single Player", {single_button.x + 20, single_button.y + 10}, 80, 10, YELLOW);
    };

    const auto draw_multi_button = [&](const Color c)
    {
        DrawRectangleRounded(multi_button, 0.6f, 20, c);
        DrawTextEx(game_font, "Multi Player", {multi_button.x + 50, multi_button.y + 10}, 80, 10, YELLOW);
    };

    draw_single_button(text_color);
    draw_multi_button(text_color);


    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, single_button))
    {
        draw_single_button(hover);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_type = GameType::SINGLE_PLAYER;
            status = Status::GAME_CHOICE;
        }
    }

    if (CheckCollisionPointRec(mousePoint, multi_button))
    {
        draw_multi_button(hover);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_type = GameType::MULTI_PLAYER;
            status = Status::GAME_RUNNING;
        }
    }
}

void qlm::TicTacToe::DrawGameChoice()
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

void qlm::TicTacToe::Toggle()
{
    turn = turn == Cell::X ? Cell::O : Cell::X;
}

void qlm::TicTacToe::DrawGrid()
{
    // Draw vertical lines
    for (int i = 1; i < game_grid.cols; i++)
    {
        DrawLineEx({i * grid_loc.width + grid_loc.x, grid_loc.y}, 
                   {i * grid_loc.width + grid_loc.x, grid_loc.y + game_grid.cols * grid_loc.height},
                   7, text_color);
    }

    // Draw horizontal lines
    for (int i = 1; i < game_grid.rows; i++)
    {
        DrawLineEx({grid_loc.x, i * grid_loc.height + grid_loc.y}, 
                   {game_grid.rows * grid_loc.width + grid_loc.x, grid_loc.y + i * grid_loc.height},
                   7, text_color);
    }

    // Loop through the grid array and draw X or O
    for (int col = 0; col < game_grid.cols; col++)
    {
        for (int row = 0; row < game_grid.rows; row++)
        {
            // Calculate the center of the current cell
            const float x_pos = row * grid_loc.width + grid_loc.x + 40;
            const float y_pos = col * grid_loc.height + grid_loc.y + 20;

            const Cell cell_value = game_grid.Get(col, row);

            if (cell_value == Cell::X)
            {
                DrawTextEx(grid_font, "X", {x_pos, y_pos}, 120, 10, GREEN);
            }
            else if (cell_value == Cell::O)
            {
                DrawTextEx(grid_font, "O", {x_pos, y_pos}, 120, 10, RED);
            }
        }
    }
}

void qlm::TicTacToe::UpdateGrid()
{
    // Get mouse position
    const Vector2 mouse_Point = GetMousePosition();
    const Color hover_color = turn == Cell::X ? GREEN : RED;

    for (int c = 0; c < game_grid.cols; c++)
    {
        for (int r = 0; r < game_grid.rows; r++)
        {
            const Cell cur_cell = game_grid.Get(c, r);

            if (cur_cell == Cell::EMPTY)
            {
                Rectangle cell = {
                    r * grid_loc.width + grid_loc.x, 
                    c * grid_loc.height + grid_loc.y,
                    (float)grid_loc.width,
                    (float)grid_loc.height
                };

                // Check if the mouse is over this cell
                if (CheckCollisionPointRec(mouse_Point, cell))
                {
                    DrawRectangleRec(cell, Fade(hover_color, 0.5f)); // hover

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        game_grid.Set(c, r, turn);
                        last_move.Set(c, r);
                        Toggle();
                        round++;
                    }
                }
            }
        }
    }
}

void qlm::TicTacToe::IsGameOver()
{
    int r = last_move.r;
    int c = last_move.c;
    
    // Check the row of the last move
    if (game_grid.Get(c, 0) == game_grid.Get(c, 1) && game_grid.Get(c, 1) == game_grid.Get(c, 2))
    {
        winner = game_grid.Get(c, 0);
    }
    // Check the column of the last move
    else if (game_grid.Get(0, r) == game_grid.Get(1, r) && game_grid.Get(1, r) == game_grid.Get(2, r))
    {
        winner = game_grid.Get(0, r);
    }
    // Check the main diagonal if the last move is on it
    else if (c == r)
    {
        if (game_grid.Get(0, 0) == game_grid.Get(1, 1) && game_grid.Get(1, 1) == game_grid.Get(2, 2))
        {
            winner = game_grid.Get(0, 0);
        }
    }
    // Check the anti-diagonal if the last move is on it
    else if (r + c == 2)
    {
        if (game_grid.Get(2, 0) == game_grid.Get(1, 1) && game_grid.Get(1, 1) == game_grid.Get(0, 2))
        {
            winner = game_grid.Get(0, 0);
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
            else if (status == Status::GAME_TYPE)
            {
                DrawGameType();
            }
            else if (status == Status::GAME_CHOICE)
            {
                DrawGameChoice();
            }
            else if (status == Status::GAME_RUNNING)
            {
                DrawGrid();
                UpdateGrid();
                if (round > 4)
                {
                    IsGameOver();

                    if (winner != Cell::EMPTY)
                    {
                        status = Status::GAME_OVER;
                    }
                }
            }
            else if (status == Status::GAME_OVER)
            {
                DrawGrid();
                // Game over menu, line of the win ?!
            }
            else 
            {
               CloseWindow();
            }
        EndDrawing();
    }
}