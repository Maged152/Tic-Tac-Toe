#include "MainMenuLayer.hpp"

qlm::MainMenuLayer::MainMenuLayer(const Font& font)
    : start_button {width / 2 - 170, 170, button_width, button_height},
      exit_button = {width / 2 - 170, 330, button_width, button_height},
      font(font),
      draw_color(text_color)
{}

qlm::MainMenuLayer::~MainMenuLayer()
{}

void qlm::MainMenuLayer::DrawButton(const Rectangle &button, const char *text, const Color text_color)
{
    DrawRectangleRounded(button, 0.6f, 20, draw_color);
    DrawTextEx(font, text, {button.x + 20, button.y + 10}, 80, 10, text_color);
}

void qlm::MainMenuLayer::OnRender()
{
    qlm::DrawButton(start_button, "START", GREEN);
    qlm::DrawButton(exit_button, "EXIT", RED);
}

qlm::Status qlm::MainMenuLayer::OnUpdate(float ts)
{
    qlm::Status status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, start_button))
    {
        draw_color = hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           status = Status::PLAY_MODE;
        }
    }
    else
    {
        draw_color = text_color;
    }

    if (CheckCollisionPointRec(mousePoint, exit_button))
    {
        draw_color = hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            status = Status::GAME_CLOSED;
        }
    }
    else
    {
        draw_color = text_color;
    }

    return status;
}