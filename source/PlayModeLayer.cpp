#include "layers/PieceSelectionLayer.hpp"
#include "layers/GameBoardLayer.hpp"
#include "layers/PlayModeLayer.hpp"
#include "TicTacToe.hpp"

qlm::PlayModeLayer::PlayModeLayer(const int width, const int height, const Font& font)
    : single_button {width / 2.0f - button_width / 2, 170, button_width, button_height},
      multi_button {width / 2.0f - button_width / 2, 330, button_width, button_height},
      Layer(font),
      single_color(qlm::glb::text_color),
      multi_color(qlm::glb::text_color)
{}

qlm::PlayModeLayer::~PlayModeLayer()
{}

void qlm::PlayModeLayer::DrawButton(const Rectangle &button,const Color button_color, const char *text, const int displacement)
{
    DrawRectangleRounded(button, 0.6f, 20, button_color);
    DrawTextEx(font, text, {button.x + displacement, button.y + 10}, 80, 10, YELLOW);
}

void qlm::PlayModeLayer::OnRender(const float ts)
{
    DrawButton(single_button, single_color, "Single Player", 20);
    DrawButton(multi_button, multi_color, "Multi Player", 50);
}

void qlm::PlayModeLayer::OnTransition(qlm::GameContext& game_context)
{
    if (game_context.status == Status::GAME_BOARD)
    {
        qlm::TicTacToe::active_layer = TransitionTo<GameBoardLayer>(game_context.width, game_context.height, game_context.font, game_context.grid);
    }
    else if (game_context.status == Status::PIECE_SELECTION)
    {
        qlm::TicTacToe::active_layer = TransitionTo<qlm::PieceSelectionLayer>(game_context.width, game_context.height, game_context.font);
    }
}

void qlm::PlayModeLayer::OnUpdate(GameContext& game_context)
{
    game_context.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, single_button))
    {
        single_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            game_context.status = Status::PIECE_SELECTION;
            game_context.game_type = GameType::SINGLE_PLAYER;
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
            game_context.status = Status::GAME_BOARD;
            game_context.game_type = GameType::MULTI_PLAYER;
        }
    }
    else
    {
        multi_color = qlm::glb::text_color;
    }
}