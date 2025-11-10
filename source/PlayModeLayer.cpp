#include "PlayModeLayer.hpp"

qlm::PlayModeLayer::PlayModeLayer(const int width, const int height, const Font& font)
    : single_button {width / 2 - button_width / 2, 170, button_width, button_height},
      multi_button = {width / 2 - button_width / 2, 330, button_width, button_height},
      font(font),
      draw_color(qlm::glb::text_color)
{}

qlm::PlayModeLayer::~PlayModeLayer()
{}

void qlm::PlayModeLayer::DrawButton(const Rectangle &button, const char *text)
{
    DrawRectangleRounded(button, 0.6f, 20, draw_color);
    DrawTextEx(font, text, {button.x + 20, button.y + 10}, 80, 10, YELLOW);
}

void qlm::PlayModeLayer::OnRender()
{
    qlm::DrawButton(single_button, "Single Player");
    qlm::DrawButton(multi_button, "Multi Player");
}

void qlm::PlayModeLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, single_button))
    {
        draw_color = hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::PIECE_SELECTION;
            game_status.gameType = GameType::SINGLE_PLAYER;
        }
    }
    else
    {
        draw_color = qlm::glb::text_color;
    }

    if (CheckCollisionPointRec(mousePoint, multi_button))
    {
        draw_color = hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::GAME_BOARD;
            game_status.gameType = GameType::MULTI_PLAYER;
        }
    }
    else
    {
        draw_color = qlm::glb::text_color;
    }
}