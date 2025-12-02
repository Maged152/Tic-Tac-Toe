#include "layers/GameExtendLayer.hpp"
#include <random>
#include <iostream>

qlm::GameExtendLayer::GameExtendLayer(const int width, const int height, const Font& text_font, qlm::Grid& grid)
        : text_font(text_font), width(width), height(height), game_grid(grid)
{
    // Find extend direction based on last move
    Location last_move = game_grid.GetLastMove();
    std::cout << "Last move x = " << last_move.x << ", y = " << last_move.y << std::endl;
    if (last_move.x == 0) 
    {
        extend_direction = Direction::LEFT;
    }
    else if (last_move.x == 2) 
    {
        extend_direction = Direction::RIGHT;
    }
    else if (last_move.y == 0)
    {
        extend_direction = Direction::UP;
    }
    else if (last_move.y == 2)
    {
        extend_direction = Direction::DOWN;
    }
    else 
    {
        // randomly choose a direction if last move is in the center
        std::random_device rd;
        std::mt19937 gen(rd());
        
        // Create a distribution from 0 to 3 (4 values)
        std::uniform_int_distribution<> dis(0, 3);
        const int dir = dis(gen);
        extend_direction = static_cast<Direction>(dir);
    }
}

qlm::GameExtendLayer::~GameExtendLayer()
{}

void qlm::GameExtendLayer::OnRender(const float ts)
{
    game_grid.DrawGrid();

    switch (extend_direction)
    {
        case Direction::LEFT:
            DrawCircle(1 * game_grid.pos.width + game_grid.pos.x + 40,  game_grid.pos.y + 20, 30, BLUE);
            break;
        case Direction::RIGHT:
            DrawCircle(1 * game_grid.pos.width + game_grid.pos.x + 40, 2 * game_grid.pos.height + game_grid.pos.y + 20, 30, RED);
            break;
        case Direction::UP:
            DrawCircle(game_grid.pos.x + 40, 1 * game_grid.pos.height + game_grid.pos.y + 20, 30, YELLOW);
            break;
        case Direction::DOWN:
            DrawCircle(2 * game_grid.pos.width + game_grid.pos.x + 40, 1 * game_grid.pos.height + game_grid.pos.y + 20, 30, BLACK);
            break;
    }
}

void qlm::GameExtendLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;
}