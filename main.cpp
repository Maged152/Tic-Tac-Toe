#include <TicTacToe.hpp>
#include <iostream>

int main() 
{
    std::cout << "Starting the game" << std::endl;
    
    qlm::TicTacToe game {};
    game.Start(60, "Tic-Tac-Toe");

    return 0;
}