#pragma once
#include "types.hpp"
#include <raylib.h>
#include <limits>
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

            const Rectangle grid_loc {width / 2 - 253, height / 2 - 180, cell_size, cell_size};

            const Color back_ground {20, 189, 172, 255};
            const Color text_color {84, 84, 84, 255};
            const Color hover {60, 60, 60, 255};

            Font game_font;
            Font grid_font;

            Status status = Status::START_MENU;
            Cell player_choice = Cell::EMPTY;
            Cell turn = Cell::X;
            GameType game_type;
            Cell winner = Cell::EMPTY;
            int round = 0;
            Location last_move;
            Grid game_grid;  

        public:
            ~TicTacToe();
            void InitTextures();
            void Start(int fps, const char* name);
            void DrawStartMenu();
            void DrawGameType();
            void DrawGameChoice();
            Cell Toggle(const Cell input);
            void DrawGrid();
            void MakeMove();
            void IsGameOver();
            void DrawGameOverMenu();
            void Reset(const Status s);
            MoveEvaluation MiniMax(const Cell player, const Location player_move, const int cur_round,
                                   int best_for_x = std::numeric_limits<int>::min(),  int best_for_o = std::numeric_limits<int>::max());
            void BestMove();
    };
}