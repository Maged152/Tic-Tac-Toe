#include "layers/GameBoardLayer.hpp"
#include <algorithm>

qlm::GameBoardLayer::GameBoardLayer(const int width, const int height, const Font& font, qlm::Grid& grid, Rectangle& grid_loc) : 
                                grid_font(font),
                                game_grid(grid),
                                grid_loc(grid_loc)
{}

qlm::GameBoardLayer::~GameBoardLayer()
{}

void qlm::GameBoardLayer::IsGameOver(GameState &game_status)
{
    game_status.winner = game_grid.IsGameOver(last_move);

    if (game_status.winner != Cell::EMPTY)
    {
        game_status.status = Status::GAME_OVER;
    }
}

void qlm::GameBoardLayer::DrawGrid()
{
    // Draw vertical lines
    for (int i = 1; i < game_grid.cols; i++)
    {
        DrawLineEx({i * grid_loc.width + grid_loc.x, grid_loc.y}, 
                   {i * grid_loc.width + grid_loc.x, grid_loc.y + game_grid.cols * grid_loc.height},
                   7, qlm::glb::text_color);
    }

    // Draw horizontal lines
    for (int i = 1; i < game_grid.rows; i++)
    {
        DrawLineEx({grid_loc.x, i * grid_loc.height + grid_loc.y}, 
                   {game_grid.rows * grid_loc.width + grid_loc.x, grid_loc.y + i * grid_loc.height},
                   7, qlm::glb::text_color);
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

qlm::Cell qlm::GameBoardLayer::Toggle(const qlm::Cell current)
{
    return current == Cell::X ? Cell::O : Cell::X;
}

void qlm::GameBoardLayer::MakeMove(qlm::GameState& game_status)
{
    hover_color = WHITE;
    // Get mouse position
    const Vector2 mouse_Point = GetMousePosition();

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
                    hover_color = turn == Cell::X ? GREEN : RED;
                    hover_cell = cell;

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

qlm::MoveEvaluation qlm::GameBoardLayer::MiniMax(const qlm::Cell player, const qlm::Location player_move, const int cur_round, int best_for_x,  int best_for_o)
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

void qlm::GameBoardLayer::BestMove(qlm::GameState &game_status)
{
    const auto best_move = MiniMax(Toggle(game_status.player_piece), last_move, round);

    // do the move
    game_grid.Set(best_move.move.r, best_move.move.c, Toggle(game_status.player_piece));
    last_move.Set(best_move.move.r, best_move.move.c);
    turn = Toggle(turn);
    round++;
}

void qlm::GameBoardLayer::OnRender(const float ts)
{
    DrawGrid();

    if (hover_color.r != 255 || hover_color.g != 255 || hover_color.b != 255)
    {
        DrawRectangleRec(hover_cell, Fade(hover_color, 0.5f));
    }
}

void qlm::GameBoardLayer::OnUpdate(qlm::GameState &game_status)
{
    game_status.status = Status::NO_CHANGE;
    if (game_status.game_type == qlm::GameType::MULTI_PLAYER)
    {
        MakeMove(game_status);
    }
    else
    {
        if (turn == game_status.player_piece) MakeMove(game_status);
        else BestMove(game_status);
    }
    
    if (round > 4)
    {
        IsGameOver(game_status);

        // check for draw
        if (round == 9)
        {
            game_status.status = game_status.game_type == GameType::MULTI_PLAYER ? Status::GAME_EXTEND : Status::GAME_OVER;
        }
    }
}