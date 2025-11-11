#include "PieceSelectionLayer.hpp"

qlm::PieceSelectionLayer::PieceSelectionLayer(const int width, const int height, const Font& font)
    : x_button {width / 2 - button_width - 20, 250, button_width, button_height},
      o_button = {width / 2 + 2, 250, button_width, button_height},
      font(font),
      x_color(qlm::glb::text_color),
      o_color(qlm::glb::text_color)
{}

qlm::PieceSelectionLayer::~PieceSelectionLayer()
{}

void qlm::PieceSelectionLayer::DrawButton(const Rectangle &button,const Color button_color, const char *text, const Color text_color)
{
    DrawRectangleRounded(button, 0.6f, 20, button_color);
    DrawTextEx(font, text, {button.x + 130, button.y + 15}, 80, 10, text_color);
}

void qlm::PieceSelectionLayer::OnRender()
{
    qlm::DrawButton(x_button, x_color, "X", GREEN);
    qlm::DrawButton(o_button, o_color, "O", RED);
}

void qlm::PieceSelectionLayer::OnUpdate(GameState& game_status)
{
    game_status.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, x_button))
    {
        x_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           game_status.status = Status::GAME_BOARD;
           game_status.playerPiece = Cell::X;
        }
    }
    else
    {
        x_color = qlm::glb::text_color;
    }

    if (CheckCollisionPointRec(mousePoint, o_button))
    {
        o_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_status.status = Status::GAME_BOARD;
            game_status.playerPiece = Cell::O;
        }
    }
    else
    {
        o_color = qlm::glb::text_color;
    }
}