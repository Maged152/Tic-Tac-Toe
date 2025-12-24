#pragma once
#include "layers/Layer.hpp"
#include <limits>
#include <memory>

namespace qlm
{
    class TicTacToe
    {
        private:
            GameContext game_context;

        public:
            TicTacToe();
            ~TicTacToe();
            void Start(int fps, const char* name);

            static constexpr int width = 1000;
            static constexpr int height = 600;
            static std::unique_ptr<Layer> active_layer;

        private:
            void InitTextures();
    };
}