#include "layers/GameExtendLayer.hpp"
#include "layers/GameBoardLayer.hpp"
#include "TicTacToe.hpp"
#include <random>

qlm::GameExtendLayer::GameExtendLayer(const int width, const int height, const Font& font, qlm::Grid& grid)
        : Layer(font), width(width), height(height), game_grid(grid)
{
    game_grid.round = 6;
    
    // randomly choose a direction if needed
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Create a distribution from 0 to 3 (4 values)
    std::uniform_int_distribution<> dis_4(0, 3);
    std::uniform_int_distribution<> dis_2(0, 1);

    // correct the last move position & Find extend direction based on last move
    Location last_move = game_grid.GetLastMove();

    if (last_move.x == 0 && last_move.y == 0) 
    {
        // Top-left corner: random between RIGHT or DOWN
        extend_direction = dis_2(gen) == 0 ? Direction::RIGHT : Direction::DOWN;
    }
    else if (last_move.x == 2 && last_move.y == 0) 
    {
        // Top-right corner: random between LEFT or DOWN
        extend_direction = dis_2(gen) == 0 ? Direction::LEFT : Direction::DOWN;
    }
    else if (last_move.x == 0 && last_move.y == 2)
    {
        // Bottom-left corner: random between RIGHT or UP
        extend_direction = dis_2(gen) == 0 ? Direction::RIGHT : Direction::UP;
    }
    else if (last_move.x == 2 && last_move.y == 2)
    {
        // Bottom-right corner: random between LEFT or UP
        extend_direction = dis_2(gen) == 0 ? Direction::LEFT : Direction::UP;
    }
    else if (last_move.x == 0) 
    {
        extend_direction = Direction::RIGHT;
    }
    else if (last_move.x == 2) 
    {
        extend_direction = Direction::LEFT;
    }
    else if (last_move.y == 0)
    {
        extend_direction = Direction::DOWN;
    }
    else if (last_move.y == 2)
    {
        extend_direction = Direction::UP;
    }
    else 
    {
        const int dir = dis_4(gen);
        extend_direction = static_cast<Direction>(dir);
    }

    switch (extend_direction) 
    {
        case Direction::RIGHT:
            game_grid.SetLastMove(last_move.x + 1, last_move.y);
            break;
        case Direction::LEFT:
            game_grid.SetLastMove(last_move.x - 1, last_move.y);
            break;
        case Direction::UP:
            game_grid.SetLastMove(last_move.x, last_move.y - 1);
            break;
        case Direction::DOWN:
            game_grid.SetLastMove(last_move.x, last_move.y + 1);
            break;
    };
}

qlm::GameExtendLayer::~GameExtendLayer()
{}

void qlm::GameExtendLayer::RemoveMoves(const Direction dir)
{
    if (dir == Direction::LEFT)
    {
        for (int y = 0; y < game_grid.rows; y++)
        {
            game_grid.Set(0, y, qlm::Cell::EMPTY);
        }
    }
    else if (dir == Direction::RIGHT)
    {
        for (int y = 0; y < game_grid.rows; y++)
        {
            game_grid.Set(2, y, qlm::Cell::EMPTY);
        }
    }
    else if (dir == Direction::UP)
    {
        for (int x = 0; x < game_grid.cols; x++)
        {
            game_grid.Set(x, 0, qlm::Cell::EMPTY);
        }
    }
    else if (dir == Direction::DOWN)
    {
        for (int x = 0; x < game_grid.cols; x++)
        {
            game_grid.Set(x, 2, qlm::Cell::EMPTY);
        }
    }

    moved = true;
}

void qlm::GameExtendLayer::ShiftGrid(const Direction dir)
{
    if (dir == Direction::LEFT)
    {
        for (int y = 0; y < game_grid.rows; y++)
        {
            game_grid.Set(0, y, game_grid.Get(1, y));
            game_grid.Set(1, y, game_grid.Get(2, y));
            game_grid.Set(2, y, qlm::Cell::EMPTY);
        }
    }
    else if (dir == Direction::RIGHT)
    {
        for (int y = 0; y < game_grid.rows; y++)
        {
            game_grid.Set(2, y, game_grid.Get(1, y));
            game_grid.Set(1, y, game_grid.Get(0, y));
            game_grid.Set(0, y, qlm::Cell::EMPTY);
        }
    }
    else if (dir == Direction::UP)
    {
        for (int x = 0; x < game_grid.cols; x++)
        {
            game_grid.Set(x, 0, game_grid.Get(x, 1));
            game_grid.Set(x, 1, game_grid.Get(x, 2));
            game_grid.Set(x, 2, qlm::Cell::EMPTY);
        }
    }
    else if (dir == Direction::DOWN)
    {
        for (int x = 0; x < game_grid.cols; x++)
        {
            game_grid.Set(x, 2, game_grid.Get(x, 1));
            game_grid.Set(x, 1, game_grid.Get(x, 0));
            game_grid.Set(x, 0, qlm::Cell::EMPTY);
        }
    }

    shifted = true;
}

void qlm::GameExtendLayer::OnRender(const float ts)
{
    game_grid.DrawGrid(font);
}

void qlm::GameExtendLayer::OnTransition(qlm::GameContext& game_context)
{
    if (game_context.status == Status::GAME_BOARD)
    {
        qlm::TicTacToe::active_layer = TransitionTo<GameBoardLayer>(game_context.width, game_context.height, game_context.font, game_context.grid);
    }
}

void qlm::GameExtendLayer::OnUpdate(GameContext& game_context)
{
    if (!moved) {
        RemoveMoves(extend_direction);
    } else if (!shifted) {
        ShiftGrid(extend_direction);
    } else {
        // Extension complete, transition back to game board
        game_context.status = qlm::Status::GAME_BOARD;
        return;
    }
    game_context.status = qlm::Status::NO_CHANGE;
}