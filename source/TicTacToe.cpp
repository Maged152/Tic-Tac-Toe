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

std::unique_ptr<qlm::Layer> qlm::TicTacToe::active_layer = nullptr;

qlm::TicTacToe::TicTacToe() : game_context(width, height)
{}

qlm::TicTacToe::~TicTacToe()
{
    UnloadFont(game_context.font);
    CloseWindow();
}

void qlm::TicTacToe::InitTextures()
{
    game_context.font = LoadFont("resources/orange juice 2.0.ttf");
}

void qlm::TicTacToe::Start(int fps, const char *name)
{
    InitWindow(width, height, name);
    SetTargetFPS(fps);

    InitTextures();

    // Start with Main Menu
    active_layer = std::make_unique<MainMenuLayer>(width, height, game_context.font);
    game_context.status = Status::NO_CHANGE;

    float last_time = GetTime();

    // game loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(qlm::glb::back_ground);
            DrawTextEx(game_context.font, "XO GAME", {width / 2 - 200, 20}, 80, 10, qlm::glb::text_color);

            float current_time = GetTime();
			float time_step = std::clamp(current_time - last_time, 0.001f, 0.1f);
			last_time = current_time;

            active_layer->OnUpdate(game_context);
            active_layer->OnRender(time_step);
            active_layer->OnTransition(game_context);
 
        EndDrawing();
    }
}