#include <iostream>
#include <vector>

class GameBoard{
    public:
        const int board_size_x; // number of rows in the grid
        const int board_size_y; // number of columns in the grid
        const int board_size_total; // area of the board (in tiles)
        std::vector<std::vector<int>> board; // the 2048 board
        std::vector<std::tuple<int,int,int>> non_zero_tiles; // contains the coordinates and value of all non-zero tiles
        std::tuple<bool, std::string> game_status; // game status, bool to determine if Game Over, String for reason of Game Over
       
        /** 
        * Initializes the game board & the random seed
        * 
        * @param size the size of the game board
        */
        GameBoard(int size);

        /**
        * Prints the Game Board to the terminal
        */
        void PrintBoard();

        /**
        * Prints the "header" for the game, only used when first starting
        */
        void PrintHeader();
        
        /**
        * Starts the game by placing 2 numbers on 2 free tiles on the board
        */
        void StartGame();
        
        /**
        * Places a new tile of value "2" in a free slot on the board
        */
        void PlaceNewTile();
        
        /**
        * Generates a pair of random coordinates within the range of the board
        * @param[out] x, y the coordinates that are generated
        */
        void GenerateRandomCoordinates(int &x, int &y);
        
        /**
        * Retrieves coordinates of all tiles with a value != 0.
        * It is used to update non_zero_tiles variable. These values are collected from "top" to "bottom",
        * "left" to "right". This characteristic is what the different Move methods were created around.
        */
        void GetNonZeroTiles(); 
        
        /**
        * "Main" move method, depending on the user input will call on the corresponding 
        * MoveUp, MoveDown, MoveLeft or MoveRight method.
        * @param direction the direction the user wishes to move using 'w', 'a', 's' or 'd'
        */
        void Move(char direction);
        
        /**
        * Moves all tiles on the board "up"
        * @return true if any tile was moved, false if all tiles stayed on the same position
        */
        bool MoveUp();
        
        /**
        * Moves all tiles on the board "down"
        * @return true if any tile was moved, false if all tiles stayed on the same position
        */
        bool MoveDown();
        
        /**
        * Moves all tiles on the board "left"
        * @return true if any tile was moved, false if all tiles stayed on the same position
        */
        bool MoveLeft();
        
        /**
        * Moves all tiles on the board "right"
        * @return true if any tile was moved, false if all tiles stayed on the same position
        */
        bool MoveRight();
        
        /**
        * Get the games current status
        * @return a bool and string tuple, true if game over, false if not, string contains reason for Game Over, "" if not over
        */
        std::tuple<bool, std::string> GameStatus();
};