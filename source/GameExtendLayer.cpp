#include "layers/GameExtendLayer.hpp"

qlm::GameExtendLayer::GameExtendLayer(const int width, const int height, const Font& grid_font, const Font& text_font, const qlm::Grid& grid, const Rectangle& grid_loc)
        : grid_font(grid_font), text_font(text_font), game_grid(grid), grid_loc(grid_loc), width(width), height(height)
{
    // Find max/min x and y coordinates in the grid
    max_x = grid_loc.x + grid_loc.width * game_grid.cols;
    min_x = grid_loc.x;

    max_y = grid_loc.y + grid_loc.height * game_grid.rows;
    min_y = grid_loc.y;
}

qlm::GameExtendLayer::~GameExtendLayer()
{}

void qlm::GameExtendLayer::DrawGrid()
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

    DrawCircle(min_x, min_y, 5.0f, BLUE);
    DrawCircle(max_x, max_y, 5.0f, BLUE);
}

void qlm::GameExtendLayer::OnRender(const float ts)
{
    DrawGrid();
}

void qlm::GameExtendLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;
}