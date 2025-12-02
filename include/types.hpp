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

    enum class Direction
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    struct Location
    {
        int x;
        int y;

        void Set(int x_loc, int y_loc)
        {
            x = x_loc;
            y = y_loc;
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
            static constexpr int cell_size = 150;
            Rectangle pos;

        private:
            Cell grid[rows][cols];
            Location last_move;
            Font& font;

        public:
            Grid(const int width, const int height, Font &font);
            Grid(const Grid& other);

            void Set(const int x, const int y, const qlm::Cell value);
            void Set(const qlm::Cell value);
            Cell Get(const int x, const int y) const;

            void SetLastMove(const int x, const int y);
            Location GetLastMove() const;

            void DrawGrid() const;
            
            Cell IsGameOver(const Location move) const;
            void Print() const;
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