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
            static const int cell_size = 100;

            Status status = Status::START_MENU;

            Color back_ground {20, 189, 172, 255};
            Color text_color {84, 84, 84, 255};
            Color hover {60, 60, 60, 255};
            Font game_font;

        public:
            ~TicTacToe();
            void InitTextures();
            void Start(int fps, const char* name);
            void DrawStartMenu();

    };
}