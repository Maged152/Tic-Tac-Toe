#include "layers/MainMenuLayer.hpp"

qlm::MainMenuLayer::MainMenuLayer(const int width, const int height, const Font& font)
    : start_button {width / 2.0f - 170, 170, button_width, button_height},
      exit_button {width / 2.0f - 170, 330, button_width, button_height},
      font(font),
      start_color(qlm::glb::text_color),
      exit_color(qlm::glb::text_color)
{}

qlm::MainMenuLayer::~MainMenuLayer()
{}

void qlm::MainMenuLayer::DrawButton(const Rectangle &button,const Color button_color, const char *text, const Color text_color, const int displacement)
{
    DrawRectangleRounded(button, 0.6f, 20, button_color);
    DrawTextEx(font, text, {button.x + displacement, button.y + 10}, 80, 10, text_color);
}

void qlm::MainMenuLayer::OnRender(const float ts)
{
    DrawButton(start_button, start_color, "START", GREEN, 20);
    DrawButton(exit_button, exit_color, "EXIT", RED, 70);
}

void qlm::MainMenuLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, start_button))
    {
        start_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           game_status.status = Status::PLAY_MODE;
        }
    }
    else
    {
        start_color = qlm::glb::text_color;
    }

    if (CheckCollisionPointRec(mousePoint, exit_button))
    {
        exit_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::GAME_CLOSED;
        }
    }
    else
    {
        exit_color = qlm::glb::text_color;
    }
}