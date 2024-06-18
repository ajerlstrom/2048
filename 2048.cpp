#include <iostream>
#include <string>
#include "board.h"

int main (){
    char move;
    GameBoard Board(4);
    Board.StartGame();
    Board.PrintHeader();
    Board.PrintBoard();

    while(!std::get<0>(Board.game_status)){
        std::cout << "Move:";
        std::cin >> move;
        Board.Move(move);
        Board.PrintBoard();
    }

    std::cout << "------------- GAME OVER -------------" << std::endl;
    std::cout << std::get<1>(Board.game_status) << std::endl;
    return 0;
}
