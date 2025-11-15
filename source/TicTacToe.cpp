#include "TicTacToe.hpp"
#include "layers/GameBoardLayer.hpp"
#include "layers/StartMenuLayer.hpp"
#include "layers/GameTypeLayer.hpp"
#include "layers/PieceSelectionLayer.hpp"
#include "layers/GameOverLayer.hpp"
#include <string>
#include <cmath>

qlm::TicTacToe::TicTacToe()
{
    InitTextures();

    // Start with Main Menu
    game_state.status = Status::START_MENU;
    active_layer = std::make_unique<MainMenuLayer>(width, height, game_font);
}

qlm::TicTacToe::~TicTacToe()
{
    UnloadFont(game_font);
    UnloadFont(grid_font);
    CloseWindow();
}

void qlm::TicTacToe::InitTextures()
{
    game_font = LoadFont("resources/orange juice 2.0.ttf");
    grid_font = LoadFont("resources/Surfing Capital.ttf");
}

void qlm::TicTacToe::Transition(const Status new_status)
{
     switch (nextStatus) {
        case Status::START_MENU:
            active_layer = std::make_unique<MainMenuLayer>(width, height, game_font);
            break;
        case Status::PLAY_MODE:
            active_layer = std::make_unique<PlayModeLayer>(width, height, game_font);
            break;
        case Status::PIECE_SELECTION:
            active_layer = std::make_unique<PieceSelectionLayer>(width, height, game_font);
            break;
        case Status::GAME_BOARD:
            active_layer = std::make_unique<GameBoardLayer>(width, height, grid_font);
            break;
        case Status::GAME_OVER:
            active_layer = std::make_unique<GameOverLayer>(width, height, game_font);
            break;
        case Status::GAME_CLOSED:
            CloseWindow();
            break;
        case Status::NO_CHANGE:
            // Do nothing
            break;
        default:
            assert(false && "TicTacToe::Transition - unhandled Status");
    }
}

void qlm::TicTacToe::Start(int fps, const char *name)
{
    InitWindow(width, height, name);
    SetTargetFPS(fps);

    // game loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(back_ground);
            DrawTextEx(game_font, "XO GAME", {width / 2 - 200, 20}, 80, 10, qlm::glb::text_color);

            active_layer->OnUpdate(game_status);
            active_layer->OnRender();
            active_layer->Transition(game_status.status);
 
        EndDrawing();
    }
}