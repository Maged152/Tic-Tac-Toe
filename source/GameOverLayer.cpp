#include "GameOverLayer.hpp"

qlm::GameOverLayer::GameOverLayer(const int width, const int height, const Font& font)
    : replay_button {width / 2 - button_width - 20, height / 2 + 20, button_width, button_height},
      main_button = {width / 2 + 20, height / 2 + 20, button_width, button_height},
      font(font),
      draw_color(qlm::glb::text_color)
{}

qlm::GameOverLayer::~GameOverLayer()
{}

void qlm::GameOverLayer::DrawButton(const Rectangle &button, const char *text, const Color c)
{
    DrawRectangleRounded(button, 0.4f, 10,  Fade(draw_color, 0.7f));
    Vector2 text_size = MeasureTextEx(font, text, 30, 5);
    DrawTextEx(game_font, text, 
                {button.x + button.width / 2 - text_size.x / 2, button.y + button.height / 2 - text_size.y / 2}, 
                30, 5, c);
}

void qlm::GameOverLayer::OnRender()
{
    if (winner == Cell::X)
        result_text = "Player X Wins!";
    else if (winner == Cell::O)
        result_text = "Player O Wins!";
    else
        result_text = "It's a Draw!";

    // Draw the result text
    DrawTextEx(font, result_text.c_str(), 
               {width / 2 - MeasureTextEx(font, result_text.c_str(), 50, 5).x / 2, height / 2 - 100}, 
               50, 5, qlm::glb::hover);
        
    DrawButton(replay_button, "Replay", GREEN);
    DrawButton(main_button, "Main Menu", RED);
}

void qlm::GameOverLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, replay_button))
    {
        draw_color = hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           game_status.status = Status::PLAY_MODE;
        }
    }
    else
    {
        draw_color = qlm::glb::text_color;
    }

    if (CheckCollisionPointRec(mousePoint, main_button))
    {
        draw_color = hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::GAME_CLOSED;
        }
    }
    else
    {
        draw_color = qlm::glb::text_color;
    }
}