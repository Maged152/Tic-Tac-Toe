#include "TicTacToe.hpp"
#include "layers/GameBoardLayer.hpp"
#include "layers/MainMenuLayer.hpp"
#include "layers/PlayModeLayer.hpp"
#include "layers/PieceSelectionLayer.hpp"
#include "layers/GameOverLayer.hpp"
#include "layers/GameExtendLayer.hpp"
#include "layers/BackgroundLayer.hpp"
#include <string>
#include <cmath>
#include <cassert>
#include <algorithm>

qlm::GameContext qlm::TicTacToe::game_context = qlm::GameContext(qlm::TicTacToe::width, qlm::TicTacToe::height);
std::unique_ptr<qlm::Layer> qlm::TicTacToe::foreground_layer = std::make_unique<MainMenuLayer>();
std::unique_ptr<qlm::Layer> qlm::TicTacToe::background_layer = std::make_unique<BackgroundLayer>();

qlm::TicTacToe::TicTacToe()
{}

qlm::TicTacToe::~TicTacToe()
{
    UnloadFont(game_context.font);
    UnloadFont(game_context.grid_font);
    CloseWindow();
}

void qlm::TicTacToe::InitTextures()
{
    game_context.font = LoadFont("resources/orange juice 2.0.ttf");
    game_context.grid_font = LoadFont("resources/Surfing Capital.ttf");
}

void qlm::TicTacToe::Start(int fps, const char *name)
{
    InitWindow(width, height, name);
    SetTargetFPS(fps);

    InitTextures();

    float last_time = GetTime();

    // game loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
            float current_time = GetTime();
			float time_step = std::clamp(current_time - last_time, 0.001f, 0.1f);
			last_time = current_time;

            // background layer
            background_layer->OnUpdate();
            background_layer->OnRender(time_step);
            background_layer->OnTransition();

            // foreground layer
            foreground_layer->OnUpdate();
            foreground_layer->OnRender(time_step);
            foreground_layer->OnTransition();
 
        EndDrawing();
    }
}