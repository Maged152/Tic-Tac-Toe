#include "types.hpp"
#include <iostream>

qlm::Grid::Grid()
{
    this->Set(qlm::Cell::EMPTY);
}

qlm::Grid::Grid(const qlm::Grid &other)
{
    for (int r = 0; r < rows; r++) 
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = other.grid[r][c];
        }
    }
}

void qlm::Grid::Set(const int r, const int c, const qlm::Cell value)
{
    // safer to check range of the input but no need for it here
    grid[r][c] = value;
}

void qlm::Grid::Set(const qlm::Cell value)
{
    for (int r = 0; r < rows; r++) 
    {
        for (int c = 0; c < cols; c++)
        {
            grid[r][c] = value;
        }
    }
}

qlm::Cell qlm::Grid::Get(const int r, const int c)
{
    // safer to check range of the input but no need for it here
    return grid[r][c];
}

qlm::Cell qlm::Grid::IsGameOver(const Location last_move)
{
    qlm::Cell winner = qlm::Cell::EMPTY;
    const int r = last_move.r;
    const int c = last_move.c;
    
    // Check the row of the last move
    if (this->Get(r, 0) == this->Get(r, 1) && this->Get(r, 1) == this->Get(r, 2))
    {
        winner = this->Get(r, 0);
    }
    // Check the column of the last move
    else if (this->Get(0, c) == this->Get(1, c) && this->Get(1, c) == this->Get(2, c))
    {
        winner = this->Get(0, c);
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
        if (this->Get(0, 2) == this->Get(1, 1) && this->Get(1, 1) == this->Get(2, 0))
        {
            winner = this->Get(0, 2);
        }
    }

    return winner;
}

std::ostream& operator<<(std::ostream& os, const qlm::Cell c) 
{
    if (c == qlm::Cell::X) std::cout << "X";
    else if (c == qlm::Cell::O) std::cout << "O";
    else  std::cout << " ";

    return os;
}
void qlm::Grid::Print()
{
    for (int r = 0; r < rows; r++)
    {
        std::cout << "| ";
        for (int c = 0; c < cols; c++)
        {
            std::cout << this->Get(r, c) << " |";
        }
        std::cout << "\n";
    }
}
