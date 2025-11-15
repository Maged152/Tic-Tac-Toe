#include "layers/GameOverLayer.hpp"

qlm::GameOverLayer::GameOverLayer(const int width, const int height, const Font& grid_font, const Font& text_font, const qlm::Grid& grid, const Rectangle& grid_loc)
        : replay_button {width / 2.0f - button_width - 20, height / 2.0f + 20, button_width, button_height},
          main_button {width / 2.0f + 20, height / 2.0f + 20, button_width, button_height},
          grid_font(grid_font),
          text_font(text_font),
          replay_color(qlm::glb::text_color),
          main_color(qlm::glb::text_color),
          game_grid(grid),
          grid_loc(grid_loc),
          width(width),
          height(height)
{}

qlm::GameOverLayer::~GameOverLayer()
{}

void qlm::GameOverLayer::DrawButton(const Rectangle &button, const Color button_color, const char *text, const Color text_color)
{
    DrawRectangleRounded(button, 0.4f, 10,  Fade(button_color, 0.7f));
    Vector2 text_size = MeasureTextEx(text_font, text, 30, 5);
    DrawTextEx(text_font, text, 
                {button.x + button.width / 2 - text_size.x / 2, button.y + button.height / 2 - text_size.y / 2}, 
                30, 5, text_color);
}

void qlm::GameOverLayer::DrawGrid()
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

void qlm::GameOverLayer::OnRender()
{
    DrawGrid();

    // Draw the result text
    DrawTextEx(text_font, result_text.c_str(), 
               {width / 2.0f - MeasureTextEx(text_font, result_text.c_str(), 50, 5).x / 2, height / 2.0f - 100}, 
               50, 5, qlm::glb::hover);
        
    DrawButton(replay_button, replay_color, "Replay", GREEN);
    DrawButton(main_button, main_color, "Main Menu", RED);
}

void qlm::GameOverLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;

    if (game_status.winner == Cell::X)
        result_text = "Player X Wins!";
    else if (game_status.winner == Cell::O)
        result_text = "Player O Wins!";
    else
        result_text = "It's a Draw!";

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, replay_button))
    {
        replay_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           game_status.status = Status::PLAY_MODE;
        }
    }
    else
    {
        replay_color = qlm::glb::text_color;
    }

    if (CheckCollisionPointRec(mousePoint, main_button))
    {
        main_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::GAME_CLOSED;
        }
    }
    else
    {
        main_color = qlm::glb::text_color;
    }
}