#include "TicTacToe.hpp"
#include <string>
#include <cmath>
#include <iostream>

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

qlm::Cell qlm::TicTacToe::Toggle(const qlm::Cell input)
{
    return input == Cell::X ? Cell::O : Cell::X;
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

            const Cell cell_value = game_grid.Get(row, col);

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

void qlm::TicTacToe::MakeMove()
{
    // Get mouse position
    const Vector2 mouse_Point = GetMousePosition();
    const Color hover_color = turn == Cell::X ? GREEN : RED;

    for (int r = 0; r < game_grid.rows; r++)
    {
        for (int c = 0; c < game_grid.cols; c++)
        {
            const Cell cur_cell = game_grid.Get(r, c);

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
                        game_grid.Set(r, c, turn);
                        last_move.Set(r, c);
                        turn = Toggle(turn);
                        round++;
                    }
                }
            }
        }
    }
}

void qlm::TicTacToe::IsGameOver()
{
    winner = game_grid.IsGameOver(last_move);

    if (winner != Cell::EMPTY)
    {
        status = Status::GAME_OVER;
    }
}

void qlm::TicTacToe::DrawGameOverMenu()
{
    // Text for winner or draw
    std::string result_text;
    if (winner == Cell::X)
        result_text = "Player X Wins!";
    else if (winner == Cell::O)
        result_text = "Player O Wins!";
    else
        result_text = "It's a Draw!";

    // Define button dimensions and positions
    const int button_width = 350;
    const int button_height = 80;

    Rectangle replay_button = {
        width / 2 - button_width - 20, 
        height / 2 + 20, 
        button_width, 
        button_height
    };

    Rectangle main_button = {
        width / 2 + 20, 
        height / 2 + 20, 
        button_width, 
        button_height
    };

    // Draw the result text
    DrawTextEx(game_font, result_text.c_str(), 
               {width / 2 - MeasureTextEx(game_font, result_text.c_str(), 50, 5).x / 2, height / 2 - 100}, 
               50, 5, hover);

    // Helper function to draw a button
    auto DrawButton = [&](const char* text, Rectangle button, const Color color, const Color textColor) {
        DrawRectangleRounded(button, 0.4f, 10,  Fade(color, 0.7f));
        Vector2 text_size = MeasureTextEx(game_font, text, 30, 5);
        DrawTextEx(game_font, text, 
                   {button.x + button.width / 2 - text_size.x / 2, button.y + button.height / 2 - text_size.y / 2}, 
                   30, 5, textColor);
    };

    // Draw buttons with default colors
    DrawButton("Replay", replay_button, text_color, GREEN);
    DrawButton("Main Menu", main_button, text_color, RED);

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Handle hover and clicks for Replay button
    if (CheckCollisionPointRec(mousePoint, replay_button))
    {
        DrawButton("Replay", replay_button, hover, GREEN);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Reset(Status::GAME_RUNNING);
        }
    }

    // Handle hover and clicks for Main Menu button
    if (CheckCollisionPointRec(mousePoint, main_button))
    {
        DrawButton("Main Menu", main_button, hover, RED);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Reset(Status::START_MENU);
        }
    }
}

void qlm::TicTacToe::Reset(const Status s)
{
    status = s;
    winner = Cell::EMPTY;
    round = 0;
    game_grid.Set(Cell::EMPTY);
    turn = Cell::X;
}

qlm::MoveEvaluation qlm::TicTacToe::MiniMax(const Cell player, const Location player_move, const int cur_round, int best_for_x,  int best_for_o)
{
    const auto GetScore = [cur_round](const qlm::Cell game_winner)
    {
        if (game_winner == qlm::Cell::X) return 10 - cur_round;  // Favor faster wins
        if (game_winner == qlm::Cell::O) return cur_round - 10;  // Favor slower losses
        return 0; // Draw or ongoing game
    };

    qlm::MoveEvaluation out;
    out.score = GetScore(game_grid.IsGameOver(player_move));

    if (out.score != 0 || cur_round == 9)
    {
        return out;   
    }

    int best_score = player == qlm::Cell::X ? -1000 : 1000;
    qlm::Location best_move {};

    // Iterate over all possible moves
    for (int r = 0; r < game_grid.rows; r++) 
    {
        for (int c = 0; c < game_grid.cols; c++) 
        {
            if (game_grid.Get(r, c) == qlm::Cell::EMPTY)
            {
                // make a move
                game_grid.Set(r, c, player);

                auto res = MiniMax(Toggle(player), {r, c}, cur_round + 1, best_for_x, best_for_o);
                const int move_score = res.score;

                // undo the move
                game_grid.Set(r, c, qlm::Cell::EMPTY);

                if (player == qlm::Cell::X)
                {
                    best_for_x = std::max(best_for_x, move_score);
                    // Maximize score for X
                    if (move_score > best_score) {
                        best_score = move_score;
                        best_move.Set(r, c);
                    }
                } 
                else 
                {
                    best_for_o = std::min(best_for_o, move_score);
                    // Minimize score for O
                    if (move_score < best_score) 
                    {
                        best_score = move_score;
                        best_move.Set(r, c);
                    }
                }

                if (best_for_o <= best_for_x) break;
            }
        }
    }

    out.move = best_move;
    out.score = best_score;

    return out;
}

void qlm::TicTacToe::BestMove()
{
    const auto best_move = MiniMax(Toggle(player_choice), last_move, round);

    std::cout << "The AI decided to go {r = " << best_move.move.r << " , c = " << best_move.move.c << "} ,with score = " << best_move.score << "\n"; 
    // do the move
    game_grid.Set(best_move.move.r, best_move.move.c, Toggle(player_choice));
    last_move.Set(best_move.move.r, best_move.move.c);
    turn = Toggle(turn);
    round++;
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
                if (game_type == qlm::GameType::MULTI_PLAYER)
                {
                    MakeMove();
                }
                else
                {
                    if (turn == player_choice) MakeMove();
                    else BestMove();
                }
                
                if (round > 4)
                {
                    IsGameOver();

                    // check for draw
                    if (round == 9)
                    {
                        status = Status::GAME_OVER;
                    }
                }
            }
            else if (status == Status::GAME_OVER)
            {
                DrawGrid();
                DrawGameOverMenu();
            }
            else 
            {
               CloseWindow();
            }
        EndDrawing();
    }
}