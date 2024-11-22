#include "types.hpp"

qlm::Grid::Grid()
{
    for (int c = 0; c < cols; c++)
    {
        for (int r = 0; r < rows; r++)
        {
            grid[c][r] = qlm::Cell::EMPTY;
        }
    }
}

void qlm::Grid::Set(const int c, const int r, const qlm::Cell value)
{
    // safer to check range of the input but no need for it here
    grid[c][r] = value;
}

qlm::Cell qlm::Grid::Get(const int c, const int r)
{
    // safer to check range of the input but no need for it here
    return grid[c][r];
}
