#include "layers/MainMenuLayer.hpp"
#include "layers/PlayModeLayer.hpp"
#include "TicTacToe.hpp"

qlm::MainMenuLayer::MainMenuLayer()
    : start_button {qlm::TicTacToe::game_context.width / 2.0f - 170, 170, button_width, button_height},
      exit_button {qlm::TicTacToe::game_context.width / 2.0f - 170, 330, button_width, button_height},
      start_color(qlm::glb::text_color),
      exit_color(qlm::glb::text_color)
{}

qlm::MainMenuLayer::~MainMenuLayer()
{}

void qlm::MainMenuLayer::DrawButton(const Rectangle &button,const Color button_color, const char *text, const Color text_color, const int displacement)
{
    DrawRectangleRounded(button, 0.6f, 20, button_color);
    DrawTextEx(qlm::TicTacToe::game_context.font, text, {button.x + displacement, button.y + 10}, 80, 10, text_color);
}

void qlm::MainMenuLayer::OnRender(const float ts)
{
    DrawButton(start_button, start_color, "START", GREEN, 20);
    DrawButton(exit_button, exit_color, "EXIT", RED, 70);
}

void qlm::MainMenuLayer::OnTransition()
{
    if (qlm::TicTacToe::game_context.status == Status::PLAY_MODE)
    {
        qlm::TicTacToe::foreground_layer = TransitionTo<PlayModeLayer>();
    }
    else if (qlm::TicTacToe::game_context.status == Status::GAME_CLOSED)
    {
        CloseWindow();
    }
}

void qlm::MainMenuLayer::OnUpdate()
{
    qlm::TicTacToe::game_context.status = qlm::Status::NO_CHANGE;

    // Get mouse position
    Vector2 mousePoint = GetMousePosition();

    // Change button color on hover
    if (CheckCollisionPointRec(mousePoint, start_button))
    {
        start_color = qlm::glb::hover;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
           qlm::TicTacToe::game_context.status = Status::PLAY_MODE;
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
            qlm::TicTacToe::game_context.status = Status::GAME_CLOSED;
        }
    }
    else
    {
        exit_color = qlm::glb::text_color;
    }
}