#include <iostream>
#include <vector>
#include "board.h"
#include <ctime>

int random;
int x_coord, y_coord; //used for coordinate generation for new '2' tile to be added
std::tuple<bool, std::string> game_status;

//initializing GameBoard object using constructor
GameBoard::GameBoard(int size) : board_size_x(size), board_size_y(size), board_size_total(size*size){
    std::srand(std::time(nullptr));
    //generating the Board using 2D vectors
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> v2(board_size_y, v1);
    board = v2;

}

//Prints out the Game Board
void GameBoard::PrintBoard(){
    for(int i = 0; i < board_size_y; i++){
        for(int j = 0; j < board_size_x; j++){
            std::cout << "   " << board[i][j] << "   ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}

//"Starts" the game by placing 2 numbers on random tiles on the board
void GameBoard::StartGame(){
    GameBoard::GenerateRandomCoordinates(x_coord, y_coord);
    board[x_coord][y_coord] = 2;
    while(board[x_coord][y_coord] != 0) GameBoard::GenerateRandomCoordinates(x_coord, y_coord);
    board[x_coord][y_coord] = 2;
}

void GameBoard::PlaceNewTile(){
    GameBoard::GenerateRandomCoordinates(x_coord, y_coord);
    while(board[x_coord][y_coord] != 0){ //if the randomly generated coordinates are occupied, rerun generation
        GameBoard::GenerateRandomCoordinates(x_coord, y_coord);
    }
    board[x_coord][y_coord] = 2;
}

void GameBoard::Move(char direction){
    GetNonZeroTiles();
    switch(direction){
        case('w'):
            MoveUp();
            break;
        case('s'):
            MoveDown();
            break;
        case('d'):
            MoveRight();
            break;
        case('a'):
            MoveLeft();
            break;
        default:
            std::cout << "This was not a valid move, please use 'w', 'a', 's' or 'd'" << std::endl;
    }
    GameBoard::PlaceNewTile();
    game_status = GameBoard::GameStatus();
}

void GameBoard::MoveUp(){ 
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(board_size_y, v1);//empty board, will end up replacing the current Game Board
    std::vector<std::tuple<int, int>> combined_tiles; //TODO: add tiles that have been combined - fixes chain combination
    bool is_move_possible = false; //TODO: return this value, if false, no move was made & prompt for new attempt
    int x, y, value;
    bool has_been_placed;

    for(std::tuple<int,int,int> coord : non_zero_tiles){//go through all non-zero tiles
        x = std::get<0>(coord);
        y = std::get<1>(coord);
        value = std::get<2>(coord);
        has_been_placed = false;

        if(x == 0) { //if x == 0, were already at the top and cant move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }
        
        for(int row = 0; row < x; row++){
            if(has_been_placed) break;
            else if (temporary_board[row][y] != 0 && temporary_board[row][y] == value){ // combination of 2 tiles
                temporary_board[row][y] = value*2;
                has_been_placed = true;
            } else if(temporary_board[row][y] == 0){ // move to empty tile
                temporary_board[row][y] = value;   
                has_been_placed = true;
            }
        }

        if(!has_been_placed) { //if tile wasnt placed after loop complete
            temporary_board[x][y] = value; //keep the tile on its original place
        }
    }
    board = temporary_board;
}

void GameBoard::MoveDown(){
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(board_size_y, v1); //empty board, will end up replacing the current Game Board

    int x, y, value;
    bool has_been_placed;
   
    for(auto coord = non_zero_tiles.rbegin(); coord != non_zero_tiles.rend(); ++coord){  //we have to loop backwards

        x = std::get<0>(*coord);
        y = std::get<1>(*coord);
        value = std::get<2>(*coord);
        has_been_placed = false;

        if(x == board_size_x - 1) { //if x == board_size_x - 1, were already at the bottom and cant move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }

        for(int row = board_size_x - 1; row > 0; row--){

            if(has_been_placed) break;
            else if (temporary_board[row][y] != 0 && temporary_board[row][y] == value){ // combination of tiles
                temporary_board[row][y] = value*2;
                has_been_placed = true;
            } else if(temporary_board[row][y] == 0){ // move to empty tile
                temporary_board[row][y] = value;
                has_been_placed = true;
            }
        }

        if(!has_been_placed) { //no move possible, stay in the same place
            temporary_board[x][y] = value; 
        }
    }
    board = temporary_board;
}

void GameBoard::MoveLeft(){
std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(board_size_y, v1);
    int x, y, value;
    bool has_been_placed;

    for(std::tuple<int,int,int> coord : non_zero_tiles){

        x = std::get<0>(coord);
        y = std::get<1>(coord);
        value = std::get<2>(coord);
        has_been_placed = false;

        if(y == 0) { //check if already at edge
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }

        for(int col = 0; col < y; col++){ //check if move or combine possible

            if(has_been_placed) break;
            else if (temporary_board[x][col] != 0 && temporary_board[x][col] == value){ //combine with existing
                temporary_board[x][col] = value*2;
                has_been_placed = true;
            } else if(temporary_board[x][col] == 0){ //move to empty
                temporary_board[x][col] = value;
                has_been_placed = true;
            }
        }

        if(!has_been_placed) { //if nothing is possible, stay
            temporary_board[x][y] = value; 
        }
    }
    board = temporary_board;
}

void GameBoard::MoveRight(){
    //we have to loop backwards
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(board_size_y, v1); //empty board, will end up replacing the current Game Board
    int x, y, value;
    bool has_been_placed;
   
    for(auto coord = non_zero_tiles.rbegin(); coord != non_zero_tiles.rend(); ++coord){  //we have to loop backwards

        x = std::get<0>(*coord);
        y = std::get<1>(*coord);
        value = std::get<2>(*coord);
        has_been_placed = false;

        if(y == board_size_y - 1) { //if y == board_size_y - 1, were already at the right and cant move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }

        for(int col = board_size_y - 1; col > 0; col--){

            if(has_been_placed) break;
            else if (temporary_board[x][col] != 0 && temporary_board[x][col] == value){ // combination of tiles
                temporary_board[x][col] = value*2;
                has_been_placed = true;
            } else if(temporary_board[x][col] == 0){ // move to empty tile
                temporary_board[x][col] = value;
                has_been_placed = true;
            }
        }

        if(!has_been_placed) { //no move possible, stay in the same place
            temporary_board[x][y] = value; 
        }
    }
    board = temporary_board;
}

// Retrieves the coordinates of all tiles with a value != 0
void GameBoard::GetNonZeroTiles(){
    std::tuple<int,int,int> coordinate;
    non_zero_tiles.clear();
    int value;
    for(int x = 0; x < board_size_x; x++){
        for(int y = 0; y < board_size_y; y++){
            if(board[x][y] != 0){
                value = board[x][y];
                coordinate = {x, y, value};
                non_zero_tiles.push_back(coordinate);
            }
        }
    }
}

void GameBoard::GenerateRandomCoordinates(int &x, int &y){
    random = std::rand();
    x = random % board_size_x;
    random = std::rand();
    y = random % board_size_y;
}

std::tuple<bool, std::string> GameBoard::GameStatus(){
    int max_val = 0;
    bool board_has_free_tile = false;
     for(int x = 0; x < board_size_x; x++){
        for(int y = 0; y < board_size_y; y++){
            if(board[x][y] >= max_val) max_val = board[x][y];
            if(board[x][y] == 0) board_has_free_tile = true;
        }
    }
    if(max_val >= 2048) return {true, "You Reached 2048! Congratulations!"};
    else if(board_has_free_tile) return {false, ""};
    else if(!board_has_free_tile) return {true, "No more free tiles, try again"};
}

void GameBoard::PrintHeader(){
    std::cout << "WELCOME TO THE GAME 2048" << std::endl;
    std::cout << "Move with 'w', 'a', 's' and 'd' followed by 'ENTER'" << std::endl;
    std::cout << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

