#include "TicTacToe.hpp"
#include "layers/GameBoardLayer.hpp"
#include "layers/MainMenuLayer.hpp"
#include "layers/PlayModeLayer.hpp"
#include "layers/PieceSelectionLayer.hpp"
#include "layers/GameOverLayer.hpp"
#include "layers/GameExtendLayer.hpp"
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>

qlm::TicTacToe::TicTacToe() : grid_loc {width / 2.0f - 253, height / 2.0f - 180, game_grid.cell_size * game_grid.cols, game_grid.cell_size * game_grid.rows},
                                game_grid(width, height, grid_font)
{}

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
    switch (new_status) {
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
            active_layer = std::make_unique<GameBoardLayer>(width, height, game_grid);
            break;
        case Status::GAME_OVER:
            active_layer = std::make_unique<GameOverLayer>(width, height, game_font, game_grid);
            break;
        case Status::GAME_EXTEND:
            active_layer = std::make_unique<GameExtendLayer>(width, height, game_font, game_grid);
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

    InitTextures();

    // Start with Main Menu
    active_layer = std::make_unique<MainMenuLayer>(width, height, game_font);
    game_status.status = Status::NO_CHANGE;

    float last_time = GetTime();

    // game loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(qlm::glb::back_ground);
            DrawTextEx(game_font, "XO GAME", {width / 2 - 200, 20}, 80, 10, qlm::glb::text_color);

            float current_time = GetTime();
			float time_step = std::clamp(current_time - last_time, 0.001f, 0.1f);
			last_time = current_time;

            active_layer->OnUpdate(game_status);
            active_layer->OnRender(time_step);
            Transition(game_status.status);
 
        EndDrawing();
    }
}