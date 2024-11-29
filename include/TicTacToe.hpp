#pragma once
#include "types.hpp"
#include <raylib.h>

namespace qlm
{
    class TicTacToe
    {
        private:
            static const int width = 1000;
            static const int height = 600;

            static const int padding_width = 200;
            static const int padding_height = 50;

            static const int cells = 9;
            static const int cell_size = 150;

            Status status = Status::START_MENU;

            Color back_ground {20, 189, 172, 255};
            Color text_color {84, 84, 84, 255};
            Color hover {60, 60, 60, 255};
            Font game_font;
            Font grid_font;

            Cell player_choice = Cell::EMPTY;
            Cell turn = Cell::X;
            GameType game_type;
            Cell winner = Cell::EMPTY;
            int round = 0;
            Location last_move;
            Grid game_grid;
            Rectangle grid_loc {width / 2 - 253, height / 2 - 180, cell_size, cell_size};

        public:
            ~TicTacToe();
            void InitTextures();
            void Start(int fps, const char* name);
            void DrawStartMenu();
            void DrawGameType();
            void DrawGameChoice();
            void Toggle();
            void DrawGrid();
            void UpdateGrid();
            void IsGameOver();
            void DrawGameOverMenu();
            void Reset();
    };
}