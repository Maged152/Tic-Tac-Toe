#include "layers/PieceSelectionLayer.hpp"
#include "layers/GameBoardLayer.hpp"
#include "TicTacToe.hpp"

qlm::PieceSelectionLayer::PieceSelectionLayer(const int width, const int height, const Font& font)
    : x_button {width / 2.0f - button_width - 20, 250, button_width, button_height},
      o_button {width / 2.0f + 2, 250, button_width, button_height},
      Layer(font),
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

void qlm::PieceSelectionLayer::OnRender(const float ts)
{
    DrawButton(x_button, x_color, "X", GREEN);
    DrawButton(o_button, o_color, "O", RED);
}

void qlm::PieceSelectionLayer::OnTransition()
{
    if (qlm::TicTacToe::game_context.status == Status::GAME_BOARD)
    {
        qlm::TicTacToe::active_layer = TransitionTo<GameBoardLayer>(qlm::TicTacToe::game_context.width, qlm::TicTacToe::game_context.height, qlm::TicTacToe::game_context.font, qlm::TicTacToe::game_context.grid);
    }
}

void qlm::PieceSelectionLayer::OnUpdate()
{
    qlm::TicTacToe::game_context.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, x_button))
    {
        x_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           qlm::TicTacToe::game_context.status = Status::GAME_BOARD;
           qlm::TicTacToe::game_context.player_piece = Cell::X;
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
            qlm::TicTacToe::game_context.status = Status::GAME_BOARD;
            qlm::TicTacToe::game_context.player_piece = Cell::O;
        }
    }
    else
    {
        o_color = qlm::glb::text_color;
    }
}