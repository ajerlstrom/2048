#include <iostream>
#include <vector>
#pragma once

class GameBoard{
    public:
        const int board_size_x;
        const int board_size_y;
        const int board_size_total;
        std::vector<std::vector<int>> board;
        std::vector<std::tuple<int,int,int>> non_zero_tiles;
        std::tuple<bool, std::string> game_status;

        GameBoard(int size);
        void PrintBoard();
        void PrintHeader();
        void StartGame();
        void PlaceNewTile();
        void GenerateRandomCoordinates(int &x, int &y);
        void GetNonZeroTiles();
        void Move(char direction);
        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        std::tuple<bool, std::string> GameStatus();   
};