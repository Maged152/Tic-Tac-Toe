#pragma once

namespace qlm
{
    enum class Status
    {
        START_MENU,
        GAME_RUNNING,
        GAME_END
    };

    enum class Cell
    {
        X,
        O,
        EMPTY
    };


    class Grid
    {
        private:
            static const int rows = 3;
            static const int cols = 3;
            Cell grid[cols][rows];

        public:
            Grid();
            void Set(const int c, const int r, const qlm::Cell value);
            void Set(const qlm::Cell value);
            Cell Get(const int c, const int r);
    };
}