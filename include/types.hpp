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
        GameType gameType = GameType::SINGLE_PLAYER;
        Cell playerPiece = Cell::EMPTY;
        Cell winner = Cell::EMPTY;
        Location lastMove;
        bool isPlayerTurn = true;

        void Reset()
        {
            status = Status::START_MENU;
            gameType = GameType::SINGLE_PLAYER;
            playerPiece = Cell::EMPTY;
            winner = Cell::EMPTY;
            lastMove = Location{ -1, -1 };
            isPlayerTurn = true;
        }
    };
}