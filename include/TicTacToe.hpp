#pragma once
#include "types.hpp"

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

        public:
            ~TicTacToe();

            void Start(int fps, const char* name);

    };
}