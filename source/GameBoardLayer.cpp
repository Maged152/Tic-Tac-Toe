#include "layers/GameBoardLayer.hpp"
#include <algorithm>

qlm::GameBoardLayer::GameBoardLayer(const int width, const int height, qlm::Grid& grid) : game_grid(grid)
{}

qlm::GameBoardLayer::~GameBoardLayer()
{}

void qlm::GameBoardLayer::IsGameOver(GameState &game_status)
{
    game_status.winner = game_grid.IsGameOver(game_grid.GetLastMove());

    if (game_status.winner != Cell::EMPTY)
    {
        game_status.status = Status::GAME_OVER;
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

    for (int y = 0; y < game_grid.rows; y++)
    {
        for (int x = 0; x < game_grid.cols; x++)
        {
            const Cell cur_cell = game_grid.Get(x, y);

            if (cur_cell == Cell::EMPTY)
            {
                Rectangle cell = {
                        x * game_grid.cell_size + game_grid.pos.x, 
                        y * game_grid.cell_size + game_grid.pos.y,
                        (float)game_grid.cell_size,
                        (float)game_grid.cell_size
                    };
                // Check if the mouse is over this cell
                if (CheckCollisionPointRec(mouse_Point, cell))
                {
                    hover_color = game_grid.turn == Cell::X ? GREEN : RED;
                    hover_cell = cell;

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        game_grid.Set(x, y, game_grid.turn);
                        game_grid.SetLastMove(x, y);
                        game_grid.turn = Toggle(game_grid.turn);
                        game_grid.round++;
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
    for (int y = 0; y < game_grid.rows; y++) 
    {
        for (int x = 0; x < game_grid.cols; x++) 
        {
            if (game_grid.Get(x, y) == qlm::Cell::EMPTY)
            {
                // make a move
                game_grid.Set(x, y, player);

                auto res = MiniMax(Toggle(player), {x, y}, cur_round + 1, best_for_x, best_for_o);
                const int move_score = res.score;

                // undo the move
                game_grid.Set(x, y, qlm::Cell::EMPTY);

                if (player == qlm::Cell::X)
                {
                    best_for_x = std::max(best_for_x, move_score);
                    // Maximize score for X
                    if (move_score > best_score) {
                        best_score = move_score;
                        best_move.Set(x, y);
                    }
                } 
                else 
                {
                    best_for_o = std::min(best_for_o, move_score);
                    // Minimize score for O
                    if (move_score < best_score) 
                    {
                        best_score = move_score;
                        best_move.Set(x, y);
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
    const auto best_move = MiniMax(Toggle(game_status.player_piece), game_grid.GetLastMove(), game_grid.round);

    // do the move
    game_grid.Set(best_move.move.x, best_move.move.y, Toggle(game_status.player_piece));
    game_grid.SetLastMove(best_move.move.x, best_move.move.y);
    game_grid.turn = Toggle(game_grid.turn);
    game_grid.round++;
}

void qlm::GameBoardLayer::OnRender(const float ts)
{
    game_grid.DrawGrid();

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
        if (game_grid.turn == game_status.player_piece) MakeMove(game_status);
        else BestMove(game_status);
    }
    
    if (game_grid.round > 4)
    {
        IsGameOver(game_status);

        // check for draw
        if (game_grid.round == 9 && game_status.status != Status::GAME_OVER)
        {
            game_status.status = game_status.game_type == GameType::MULTI_PLAYER ? Status::GAME_EXTEND : Status::GAME_OVER;
        }
    }
}