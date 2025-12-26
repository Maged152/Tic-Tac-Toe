#include "layers/GameBoardLayer.hpp"
#include "layers/GameOverLayer.hpp"
#include "layers/GameExtendLayer.hpp"
#include "TicTacToe.hpp"
#include <algorithm>

qlm::GameBoardLayer::GameBoardLayer()
{}

qlm::GameBoardLayer::~GameBoardLayer()
{}

void qlm::GameBoardLayer::IsGameOver(GameContext &game_context)
{
    game_context.winner = game_context.grid.IsGameOver(game_context.grid.GetLastMove());

    if (game_context.winner != Cell::EMPTY)
    {
        game_context.status = Status::GAME_OVER;
    }
}


qlm::Cell qlm::GameBoardLayer::Toggle(const qlm::Cell current)
{
    return current == Cell::X ? Cell::O : Cell::X;
}

void qlm::GameBoardLayer::MakeMove(qlm::GameContext& game_context)
{
    hover_color = WHITE;
    // Get mouse position
    const Vector2 mouse_Point = GetMousePosition();

    for (int y = 0; y < game_context.grid.rows; y++)
    {
        for (int x = 0; x < game_context.grid.cols; x++)
        {
            const Cell cur_cell = game_context.grid.Get(x, y);
            if (cur_cell == Cell::EMPTY)
            {
                Rectangle cell = {
                        x * game_context.grid.cell_size + game_context.grid.pos.x, 
                        y * game_context.grid.cell_size + game_context.grid.pos.y,
                        (float)game_context.grid.cell_size,
                        (float)game_context.grid.cell_size
                    };
                // Check if the mouse is over this cell
                if (CheckCollisionPointRec(mouse_Point, cell))
                {
                    hover_color = game_context.grid.turn == Cell::X ? GREEN : RED;
                    hover_cell = cell;

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        game_context.grid.Set(x, y, game_context.grid.turn);
                        game_context.grid.SetLastMove(x, y);
                        game_context.grid.turn = Toggle(game_context.grid.turn);
                        game_context.grid.round++;
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
    out.score = GetScore(qlm::TicTacToe::game_context.grid.IsGameOver(player_move));

    if (out.score != 0 || cur_round == 9)
    {
        return out;   
    }

    int best_score = player == qlm::Cell::X ? -1000 : 1000;
    qlm::Location best_move {};

    // Iterate over all possible moves
    for (int y = 0; y < qlm::TicTacToe::game_context.grid.rows; y++) 
    {
        for (int x = 0; x < qlm::TicTacToe::game_context.grid.cols; x++) 
        {
            if (qlm::TicTacToe::game_context.grid.Get(x, y) == qlm::Cell::EMPTY)
            {
                // make a move
                qlm::TicTacToe::game_context.grid.Set(x, y, player);

                auto res = MiniMax(Toggle(player), {x, y}, cur_round + 1, best_for_x, best_for_o);
                const int move_score = res.score;

                // undo the move
                qlm::TicTacToe::game_context.grid.Set(x, y, qlm::Cell::EMPTY);

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

void qlm::GameBoardLayer::BestMove(qlm::GameContext &game_context)
{
    const auto best_move = MiniMax(Toggle(game_context.player_piece), game_context.grid.GetLastMove(), game_context.grid.round);

    // do the move
    game_context.grid.Set(best_move.move.x, best_move.move.y, Toggle(game_context.player_piece));
    game_context.grid.SetLastMove(best_move.move.x, best_move.move.y);
    game_context.grid.turn = Toggle(game_context.grid.turn);
    game_context.grid.round++;
}

void qlm::GameBoardLayer::OnRender(const float ts)
{
    qlm::TicTacToe::game_context.grid.DrawGrid(qlm::TicTacToe::game_context.grid_font);

    if (hover_color.r != 255 || hover_color.g != 255 || hover_color.b != 255)
    {
        DrawRectangleRec(hover_cell, Fade(hover_color, 0.5f));
    }
}

void qlm::GameBoardLayer::OnTransition()
{
    if (qlm::TicTacToe::game_context.status == Status::GAME_EXTEND)
    {
        qlm::TicTacToe::foreground_layer = TransitionTo<GameExtendLayer>();
    }
    else if (qlm::TicTacToe::game_context.status == Status::GAME_OVER)
    {
        qlm::TicTacToe::foreground_layer = TransitionTo<GameOverLayer>();
    }
}

void qlm::GameBoardLayer::OnUpdate()
{
    qlm::TicTacToe::game_context.status = Status::NO_CHANGE;
    if (qlm::TicTacToe::game_context.game_type == qlm::GameType::MULTI_PLAYER)
    {
        MakeMove(qlm::TicTacToe::game_context);
    }
    else
    {
        if (qlm::TicTacToe::game_context.grid.turn == qlm::TicTacToe::game_context.player_piece) MakeMove(qlm::TicTacToe::game_context);
        else BestMove(qlm::TicTacToe::game_context);
    }
    
    if (qlm::TicTacToe::game_context.grid.round > 4)
    {
        IsGameOver(qlm::TicTacToe::game_context);

        // check for draw
        if (qlm::TicTacToe::game_context.grid.round == 9 && qlm::TicTacToe::game_context.status != Status::GAME_OVER)
        {
            qlm::TicTacToe::game_context.status = qlm::TicTacToe::game_context.game_type == GameType::MULTI_PLAYER ? Status::GAME_EXTEND : Status::GAME_OVER;
        }
    }
}