#pragma once
#include "layers/Layer.hpp"
#include <limits>
#include <memory>

namespace qlm
{
    class TicTacToe
    {
        public:
            TicTacToe();
            ~TicTacToe();
            void Start(int fps, const char* name);

            static constexpr int width = 1000;
            static constexpr int height = 600;
            static std::unique_ptr<Layer> foreground_layer;
            static std::unique_ptr<Layer> background_layer;
            static GameContext game_context;

        private:
            void InitTextures();
    };
}