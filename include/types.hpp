#pragma once

namespace qlm
{
    enum class Status
    {
        START_MENU,
        GAME_TYPE,
        GAME_CHOICE,
        GAME_RUNNING,
        GAME_OVER,
        GAME_CLOSED
    };

    enum class Cell
    {
        X,
        O,
        EMPTY
    };

    enum class GameType
    {
        SINGLE_PLAYER,
        MULTI_PLAYER
    };

    struct Location
    {
        int c;
        int r;

        void Set(int c_loc, int r_loc)
        {
            c = c_loc;
            r = r_loc;
        }
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
            Cell IsGameOver(const Location& last_move);
    };
}