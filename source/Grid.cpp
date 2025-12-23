#include "types.hpp"
#include <iostream>

qlm::Grid::Grid(const int width, const int height) :
     pos {width / 2.0f - 253, height / 2.0f - 180, qlm::Grid::cell_size * qlm::Grid::Grid::cols, qlm::Grid::Grid::cell_size * qlm::Grid::Grid::rows}
{
    this->Set(qlm::Cell::EMPTY);
}

qlm::Grid::Grid(const qlm::Grid &other) : pos {other.pos}
{
    for (int y = 0; y < rows; y++) 
    {
        for (int x = 0; x < cols; x++)
        {
            grid[y][x] = other.grid[y][x];
        }
    }
}

void qlm::Grid::Set(const int x, const int y, const qlm::Cell value)
{
    // safer to check range of the input but no need for it here
    grid[y][x] = value;
}

void qlm::Grid::Set(const qlm::Cell value)
{
    for (int y = 0; y < rows; y++) 
    {
        for (int x = 0; x < cols; x++)
        {
            grid[y][x] = value;
        }
    }
}

qlm::Cell qlm::Grid::Get(const int x, const int y) const
{
    return grid[y][x];
}

void qlm::Grid::SetLastMove(const int x, const int y)
{
    last_move.Set(x, y);
}

qlm::Location qlm::Grid::GetLastMove() const
{
    return last_move;
}

qlm::Cell qlm::Grid::IsGameOver(const Location move) const
{
    qlm::Cell winner = qlm::Cell::EMPTY;
    const int y = move.y;
    const int x = move.x;
    
    // Check the row of the last move
    if (this->Get(0, y) == this->Get(1, y) && this->Get(1, y) == this->Get(2, y))
    {
        winner = this->Get(0, y);
    }
    // Check the column of the last move
    else if (this->Get(x, 0) == this->Get(x, 1) && this->Get(x, 1) == this->Get(x, 2))
    {
        winner = this->Get(x, 0);
    }
    // Check the main diagonal if the last move is on it
    else if (x == y)
    {
        if (this->Get(0, 0) == this->Get(1, 1) && this->Get(1, 1) == this->Get(2, 2))
        {
            winner = this->Get(0, 0);
        }
    }
    // Check the anti-diagonal if the last move is on it
    else if (y + x == 2)
    {
        if (this->Get(2, 0) == this->Get(1, 1) && this->Get(1, 1) == this->Get(0, 2))
        {
            winner = this->Get(2, 0);
        }
    }

    return winner;
}

void qlm::Grid::DrawGrid(const Font& font) const
{
    // Draw vertical lines
    for (int i = 1; i < cols; i++)
    {
        DrawLineEx({i * cell_size + pos.x, pos.y}, 
                   {i * cell_size + pos.x, pos.y + rows * cell_size},
                   7, qlm::glb::text_color);
    }

    // Draw horizontal lines
    for (int i = 1; i < rows; i++)
    {
        DrawLineEx({pos.x, i * cell_size + pos.y}, 
                   {pos.x + cols * cell_size, pos.y + i * cell_size},
                   7, qlm::glb::text_color);
    }

    // Loop through the grid array and draw X or O
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            // Calculate the center of the current cell
            const float x_pos = x * cell_size + pos.x + 40;
            const float y_pos = y * cell_size + pos.y + 20;

            const Cell cell_value = Get(x, y);

            if (cell_value == Cell::X)
            {
                DrawTextEx(font, "X", {x_pos, y_pos}, 120, 10, GREEN);
            }
            else if (cell_value == Cell::O)
            {
                DrawTextEx(font, "O", {x_pos, y_pos}, 120, 10, RED);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const qlm::Cell c) 
{
    if (c == qlm::Cell::X) std::cout << "X";
    else if (c == qlm::Cell::O) std::cout << "O";
    else  std::cout << " ";

    return os;
}
void qlm::Grid::Print() const
{
    for (int y = 0; y < rows; y++)
    {
        std::cout << "| ";
        for (int x = 0; x < cols; x++)
        {
            std::cout << this->Get(x, y) << " |";
        }
        std::cout << "\n";
    }
}
