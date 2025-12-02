#pragma once
#include "layers/Layer.hpp"
#include <limits>
#include <memory>

namespace qlm
{
    class TicTacToe
    {
        private:
            static constexpr int width = 1000;
            static constexpr int height = 600;

            Font game_font;
            Font grid_font;

            GameState game_status;

            Grid game_grid;
            Rectangle grid_loc;

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