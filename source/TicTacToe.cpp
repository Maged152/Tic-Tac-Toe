#include "TicTacToe.hpp"
#include <raylib.h>

qlm::TicTacToe::~TicTacToe()
{
    CloseWindow();
}

void qlm::TicTacToe::Start(int fps, const char *name)
{
    InitWindow(width, height, name);
    SetTargetFPS(fps);

    // game loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

            if (status == Status::START_MENU)
            {
                
            }
            else if (status == Status::GAME_RUNNING)
            {

            }
            else 
            {
               
            }
        EndDrawing();
    }
}