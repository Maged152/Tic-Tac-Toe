#include "layers/GameOverLayer.hpp"

qlm::GameOverLayer::GameOverLayer(const int width, const int height, const Font& text_font, qlm::Grid& grid)
        : replay_button {width / 2.0f - button_width - 20, height / 2.0f + 20, button_width, button_height},
          main_button {width / 2.0f + 20, height / 2.0f + 20, button_width, button_height},
          text_font(text_font),
          replay_color(qlm::glb::text_color),
          main_color(qlm::glb::text_color),
          width(width),
          height(height),
          game_grid(grid)
{}

qlm::GameOverLayer::~GameOverLayer()
{
    // reset the grid
    game_grid.Set(qlm::Cell::EMPTY);
    game_grid.round = 0;
    game_grid.turn = qlm::Cell::X;
}

void qlm::GameOverLayer::DrawButton(const Rectangle &button, const Color button_color, const char *text, const Color text_color)
{
    DrawRectangleRounded(button, 0.4f, 10,  Fade(button_color, 0.7f));
    Vector2 text_size = MeasureTextEx(text_font, text, 30, 5);
    DrawTextEx(text_font, text, 
                {button.x + button.width / 2 - text_size.x / 2, button.y + button.height / 2 - text_size.y / 2}, 
                30, 5, text_color);
}

void qlm::GameOverLayer::OnRender(const float ts)
{
    game_grid.DrawGrid();

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
           game_status.status = Status::GAME_BOARD;
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
            game_status.status = Status::START_MENU;
        }
    }
    else
    {
        main_color = qlm::glb::text_color;
    }
}