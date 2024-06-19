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

        GameBoard(int size); // constructor
        void PrintBoard(); // prints the board to terminal
        void PrintHeader(); // prints the "header"/introduction text
        void StartGame(); // starts the 2048 game
        void PlaceNewTile(); // places an empty tile on board
        void GenerateRandomCoordinates(int &x, int &y); // generate a random pair of coordinates
        void GetNonZeroTiles(); // updates non_zero_tiles variable
        void Move(char direction); // general move method
        bool MoveUp();
        bool MoveDown();
        bool MoveLeft();
        bool MoveRight();
        std::tuple<bool, std::string> GameStatus();  //returns game stats, stored in game_status variable 
};