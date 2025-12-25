#include "layers/GameOverLayer.hpp"
#include "layers/GameBoardLayer.hpp"
#include "layers/MainMenuLayer.hpp"
#include "TicTacToe.hpp"

qlm::GameOverLayer::GameOverLayer()
        : replay_button {qlm::TicTacToe::game_context.width / 2.0f - button_width - 20, qlm::TicTacToe::game_context.height / 2.0f + 20, button_width, button_height},
          main_button {qlm::TicTacToe::game_context.width / 2.0f + 20, qlm::TicTacToe::game_context.height / 2.0f + 20, button_width, button_height},
          replay_color(qlm::glb::text_color),
          main_color(qlm::glb::text_color)
{}

qlm::GameOverLayer::~GameOverLayer()
{
    // reset the grid
    qlm::TicTacToe::game_context.grid.Set(qlm::Cell::EMPTY);
    qlm::TicTacToe::game_context.grid.round = 0;
    qlm::TicTacToe::game_context.grid.turn = qlm::Cell::X;
}

void qlm::GameOverLayer::DrawButton(const Rectangle &button, const Color button_color, const char *text, const Color text_color)
{
    DrawRectangleRounded(button, 0.4f, 10,  Fade(button_color, 0.7f));
    Vector2 text_size = MeasureTextEx(qlm::TicTacToe::game_context.font, text, 30, 5);
    DrawTextEx(qlm::TicTacToe::game_context.font, text, 
                {button.x + button.width / 2 - text_size.x / 2, button.y + button.height / 2 - text_size.y / 2}, 
                30, 5, text_color);
}

void qlm::GameOverLayer::OnRender(const float ts)
{
    qlm::TicTacToe::game_context.grid.DrawGrid(qlm::TicTacToe::game_context.grid_font);

    // Draw the result text
    DrawTextEx(qlm::TicTacToe::game_context.font, result_text.c_str(), 
               {qlm::TicTacToe::game_context.width / 2.0f - MeasureTextEx(qlm::TicTacToe::game_context.font, result_text.c_str(), 50, 5).x / 2, qlm::TicTacToe::game_context.height / 2.0f - 100}, 
               50, 5, qlm::glb::hover);
        
    DrawButton(replay_button, replay_color, "Replay", GREEN);
    DrawButton(main_button, main_color, "Main Menu", RED);
}

void qlm::GameOverLayer::OnTransition()
{
    if (qlm::TicTacToe::game_context.status == Status::GAME_BOARD)
    {
        qlm::TicTacToe::active_layer = TransitionTo<GameBoardLayer>();
    }
    else if (qlm::TicTacToe::game_context.status == Status::START_MENU)
    {
        qlm::TicTacToe::active_layer = TransitionTo<MainMenuLayer>();
    }
}

void qlm::GameOverLayer::OnUpdate()
{
    qlm::TicTacToe::game_context.status = qlm::Status::NO_CHANGE;

    if (qlm::TicTacToe::game_context.winner == Cell::X)
        result_text = "Player X Wins!";
    else if (qlm::TicTacToe::game_context.winner == Cell::O)
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
           qlm::TicTacToe::game_context.status = Status::GAME_BOARD;
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
            qlm::TicTacToe::game_context.status = Status::START_MENU;
        }
    }
    else
    {
        main_color = qlm::glb::text_color;
    }
}