#pragma once

namespace qlm
{
    enum class Status
    {
        START_MENU,
        GAME_MENU,
        GAME_RUNNING,
        GAME_END,
        GAME_CLOSED
    };

    enum class Cell
    {
        X,
        O,
        EMPTY
    };


    class Grid
    {
        public:
            static const int rows = 3;
            static const int cols = 3;

        private:
            Cell grid[cols][rows];

        public:
            Grid();
            void Set(const int c, const int r, const qlm::Cell value);
            void Set(const qlm::Cell value);
            Cell Get(const int c, const int r);
    };
}