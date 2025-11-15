#include "layers/PlayModeLayer.hpp"

qlm::PlayModeLayer::PlayModeLayer(const int width, const int height, const Font& font)
    : single_button {width / 2.0f - button_width / 2, 170, button_width, button_height},
      multi_button {width / 2.0f - button_width / 2, 330, button_width, button_height},
      font(font),
      single_color(qlm::glb::text_color),
      multi_color(qlm::glb::text_color)
{}

qlm::PlayModeLayer::~PlayModeLayer()
{}

void qlm::PlayModeLayer::DrawButton(const Rectangle &button,const Color button_color, const char *text)
{
    DrawRectangleRounded(button, 0.6f, 20, button_color);
    DrawTextEx(font, text, {button.x + 20, button.y + 10}, 80, 10, YELLOW);
}

void qlm::PlayModeLayer::OnRender()
{
    DrawButton(single_button, single_color, "Single Player");
    DrawButton(multi_button, multi_color, "Multi Player");
}

void qlm::PlayModeLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, single_button))
    {
        single_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::PIECE_SELECTION;
            game_status.game_type = GameType::SINGLE_PLAYER;
        }
    }
    else
    {
        single_color = qlm::glb::text_color;
    }

    if (CheckCollisionPointRec(mousePoint, multi_button))
    {
        multi_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::GAME_BOARD;
            game_status.game_type = GameType::MULTI_PLAYER;
        }
    }
    else
    {
        multi_color = qlm::glb::text_color;
    }
}