#pragma once
#include "Layer.hpp"
#include <limits>
#include <memory>

namespace qlm
{
    class TicTacToe
    {
        private:
            static const int width = 1000;
            static const int height = 600;

            Font game_font;
            Font grid_font;

            GameState game_status;

            std::unique_ptr<Layer> active_layer;

        public:
            TicTacToe();
            ~TicTacToe();
            void Start(int fps, const char* name);

        private:
            void InitTextures();
            void Transition(const Status new_status);
    };
}