#include "types.hpp"

qlm::Grid::Grid()
{
    this->Set(qlm::Cell::EMPTY);
}

void qlm::Grid::Set(const int c, const int r, const qlm::Cell value)
{
    // safer to check range of the input but no need for it here
    grid[c][r] = value;
}

void qlm::Grid::Set(const qlm::Cell value)
{
    for (int c = 0; c < cols; c++)
    {
        for (int r = 0; r < rows; r++)
        {
            grid[c][r] = value;
        }
    }
}

qlm::Cell qlm::Grid::Get(const int c, const int r)
{
    // safer to check range of the input but no need for it here
    return grid[c][r];
}

qlm::Cell qlm::Grid::IsGameOver(const Location &last_move)
{
    qlm::Cell winner = qlm::Cell::EMPTY;
    int r = last_move.r;
    int c = last_move.c;
    
    // Check the row of the last move
    if (this->Get(c, 0) == this->Get(c, 1) && this->Get(c, 1) == this->Get(c, 2))
    {
        winner = this->Get(c, 0);
    }
    // Check the column of the last move
    else if (this->Get(0, r) == this->Get(1, r) && this->Get(1, r) == this->Get(2, r))
    {
        winner = this->Get(0, r);
    }
    // Check the main diagonal if the last move is on it
    else if (c == r)
    {
        if (this->Get(0, 0) == this->Get(1, 1) && this->Get(1, 1) == this->Get(2, 2))
        {
            winner = this->Get(0, 0);
        }
    }
    // Check the anti-diagonal if the last move is on it
    else if (r + c == 2)
    {
        if (this->Get(2, 0) == this->Get(1, 1) && this->Get(1, 1) == this->Get(0, 2))
        {
            winner = this->Get(0, 0);
        }
    }

    return winner;
}
