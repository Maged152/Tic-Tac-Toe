#pragma once
#include "Colors.hpp"
namespace qlm
{
    enum class Status
    {
        START_MENU,
        PLAY_MODE,
        PIECE_SELECTION,
        GAME_BOARD,
        GAME_OVER,
        GAME_CLOSED,
        GAME_EXTEND,
        NO_CHANGE
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
        int r;
        int c;

        void Set(int r_loc, int c_loc)
        {
            c = c_loc;
            r = r_loc;
        }
    };

    struct MoveEvaluation 
    {
        int score;
        Location move;
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
            Grid(const Grid& other);
            void Set(const int c, const int r, const qlm::Cell value);
            void Set(const qlm::Cell value);
            Cell Get(const int c, const int r);
            Cell IsGameOver(const Location last_move);
            void Print();
    };

    struct GameState
    {
        Status status = Status::START_MENU;
        GameType game_type = GameType::SINGLE_PLAYER;
        Cell player_piece = Cell::EMPTY;
        Cell winner = Cell::EMPTY;

        void Reset()
        {
            status = Status::START_MENU;
            game_type = GameType::SINGLE_PLAYER;
            player_piece = Cell::EMPTY;
            winner = Cell::EMPTY;
        }
    };
}