#pragma once
#include "types.hpp"

namespace qlm
{
    class TicTacToe
    {
        private:
            int width;
            int height;

            Status status = Status::GAME_RUNNING;

        public:
            TicTacToe(const int width = 1920, const int height = 1000);
            ~TicTacToe();

            void Start(int fps, const char* name);

    };
}