#include <iostream>
#include <vector>
#include <ctime>

#include "board.h"

int random;
int x_coord, y_coord; //used for coordinate generation for new '2' tile to be added

GameBoard::GameBoard(int size) : board_size_x(size), board_size_y(size), board_size_total(size*size){
    std::srand(std::time(nullptr));
    std::vector<int> v1(this->board_size_x, 0);
    std::vector<std::vector<int>> v2(this->board_size_y, v1);
    this->board = v2;
}

void GameBoard::PrintBoard(){
    for(int i = 0; i < this->board_size_y; i++){
        for(int j = 0; j < this->board_size_x; j++){
            std::cout << "   " << this->board[i][j] << "   ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;
}


void GameBoard::StartGame(){
    this->GenerateRandomCoordinates(x_coord, y_coord);
    this->board[x_coord][y_coord] = 2;
    while(board[x_coord][y_coord] != 0) this->GenerateRandomCoordinates(x_coord, y_coord); // prevent 2nd tile spawning on the 1st
    this->board[x_coord][y_coord] = 2;
}

void GameBoard::PlaceNewTile(){
    this->GenerateRandomCoordinates(x_coord, y_coord);

    while(this->board[x_coord][y_coord] != 0){ // if random tile not empty, rerun generation
        this->GenerateRandomCoordinates(x_coord, y_coord);
    }
    this->board[x_coord][y_coord] = 2;
}

void GameBoard::Move(char direction){
    bool has_moved = false; // used to determine if any tiles were moved
    GetNonZeroTiles(); // fetch all non-zero tiles
    switch(direction){
        case('w'):
            has_moved = MoveUp();
            break;
        case('s'):
            has_moved = MoveDown();
            break;
        case('d'):
            has_moved = MoveRight();
            break;
        case('a'):
            has_moved = MoveLeft();
            break;
        default:
            std::cout << "This was not a valid move, please use 'w', 'a', 's' or 'd'" << std::endl;
    }

    if(has_moved){ // if we haven't moved, we fake that "nothing happened" by not spawning a new tile
        GameBoard::PlaceNewTile(); // if we moved, we spawn a new tile on the board
    } 
    this->game_status = GameBoard::GameStatus();
    
}

bool GameBoard::MoveUp(){ 
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(this->board_size_y, v1); // empty board, will be populated with new tile locations

    int x, y, value;
    bool has_been_placed; // used to determine if the tile has been placed
    bool has_moved = false; // true if a tile has been "moved", returned at the end

    for(std::tuple<int,int,int> coord : this->non_zero_tiles){ // go through all non-zero tiles
        x = std::get<0>(coord);
        y = std::get<1>(coord);
        value = std::get<2>(coord);
        has_been_placed = false;

        if(x == 0) { // if true, we're already at the top and can't move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }
        
        for(int row = 0; row < x; row++){ // go through "x" column in temp board from "top" to "bottom" until/if the tile is placed
            if(has_been_placed) break;
            else if (temporary_board[row][y] != 0 && temporary_board[row][y] == value){ // combination of 2 tiles
                temporary_board[row][y] = value*2;
                has_been_placed = true;
                has_moved = true;
            } else if(temporary_board[row][y] == 0){ // move to empty tile
                temporary_board[row][y] = value;   
                has_been_placed = true;
                has_moved = true;
            }
        }

        if(!has_been_placed) { // if tile wasn't placed during loop
            temporary_board[x][y] = value; // tile is kept on its original place
        }
    }

    this->board = temporary_board; // update the Game Board with the new layout
    return has_moved;
}


bool GameBoard::MoveDown(){ // TODO solve issue with tiles switching position
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(this->board_size_y, v1); // empty board, will be populated with new tile locations

    int x, y, value;
    bool has_been_placed; // used to determine if the tile has been placed
    bool has_moved = false; // true if a tile has been "moved", returned at the end
   
    for(auto coord = this->non_zero_tiles.rbegin(); coord != this->non_zero_tiles.rend(); ++coord){  // go through all non-zero tiles backwards
        x = std::get<0>(*coord);
        y = std::get<1>(*coord);
        value = std::get<2>(*coord);
        has_been_placed = false;

        if(x == board_size_x - 1) { // if true, we're already at the bottom and can't move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }

        for(int row = board_size_x - 1; row > x; row--){ // go through "x" column in temp board from "bottom" to "top" until/if the tile is placed

            if(has_been_placed) break;
            else if (temporary_board[row][y] != 0 && temporary_board[row][y] == value){ // combination of tiles
                temporary_board[row][y] = value*2;
                has_been_placed = true; 
                has_moved = true;
            } else if(temporary_board[row][y] == 0){ // move to empty tile
                temporary_board[row][y] = value;
                has_been_placed = true; 
                has_moved = true;
            }
        }

        if(!has_been_placed) { // if tile wasn't placed during loop
            temporary_board[x][y] = value; 
        }
    }
    this->board = temporary_board; // update Game Board with new layout
    return has_moved;
}


bool GameBoard::MoveLeft(){ // TODO solve issue with tiles switching position
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(this->board_size_y, v1); // empty board, will be populated with new tile locations

    int x, y, value;
    bool has_been_placed; // used to determine if the tile has been placed
    bool has_moved = false; // true if a tile has been moved, is returned at the end

    for(std::tuple<int,int,int> coord : non_zero_tiles){ // go through all non-zero tiles
        x = std::get<0>(coord);
        y = std::get<1>(coord);
        value = std::get<2>(coord);
        has_been_placed = false;

        if(y == 0) { // if true, we're already at the edge and can't move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }

        for(int col = 0; col < y; col++){ // go through "y" row in temp board from "left" to "right" until/if the tile is placed

            if(has_been_placed) break;
            else if (temporary_board[x][col] != 0 && temporary_board[x][col] == value){ // combine with existing
                temporary_board[x][col] = value*2;
                has_been_placed = true;
                has_moved = true;
                
            } else if(temporary_board[x][col] == 0){ // move to empty
                temporary_board[x][col] = value;
                has_been_placed = true;
                has_moved = true;
            }
        }

        if(!has_been_placed) { // if tile wasn't placed during loop
            temporary_board[x][y] = value; 
        }
    }
    this->board = temporary_board; // update Game Board with new layout
    return has_moved;
}

bool GameBoard::MoveRight(){ 
    std::vector<int> v1(board_size_x, 0);
    std::vector<std::vector<int>> temporary_board(this->board_size_y, v1); // empty board, will be populated with new tile locations

    int x, y, value;
    bool has_been_placed; // used to determine if the tile has been placed
    bool has_moved = false; // true if a tile has been moved, is returned at the end
   
    for(auto coord = non_zero_tiles.rbegin(); coord != non_zero_tiles.rend(); ++coord){  // go through all non-zero tiles backwards
        x = std::get<0>(*coord);
        y = std::get<1>(*coord);
        value = std::get<2>(*coord);
        has_been_placed = false;

        if(y == board_size_y - 1) { // if true, we're already at the right and cant move
            temporary_board[x][y] = value; 
            has_been_placed = true;
        }

        for(int col = board_size_y - 1; col > y; col--){ // go through "y" row in temp board from "right" to "left" until/if the tile is placed

            if(has_been_placed) break;
            else if (temporary_board[x][col] != 0 && temporary_board[x][col] == value){ // combination of tiles
                temporary_board[x][col] = value*2;
                has_been_placed = true;
                has_moved = true;
            } else if(temporary_board[x][col] == 0){ // move to empty tile
                temporary_board[x][col] = value;
                has_been_placed = true;
                has_moved = true;
            }
        }

        if(!has_been_placed) { // if tile wasn't placed during loop
            temporary_board[x][y] = value; 
        }
    }
    this->board = temporary_board; // update Game Board with new layout
    return has_moved;
}

void GameBoard::GetNonZeroTiles(){
    std::tuple<int,int,int> coordinate;
    this->non_zero_tiles.clear();
    int value;

    for(int x = 0; x < this->board_size_x; x++){
        for(int y = 0; y < this->board_size_y; y++){
            if(board[x][y] != 0){
                value = this->board[x][y];
                coordinate = {x, y, value};
                this->non_zero_tiles.push_back(coordinate);
            }
        }
    }
}

void GameBoard::GenerateRandomCoordinates(int &x, int &y){
    random = std::rand();
    x = random % this->board_size_x;
    random = std::rand();
    y = random % this->board_size_y;
}

std::tuple<bool, std::string> GameBoard::GameStatus(){
    int max_val = 0;
    bool board_has_free_tile = false;
     for(int x = 0; x < this->board_size_x; x++){
        for(int y = 0; y < this->board_size_y; y++){
            if(this->board[x][y] >= max_val) max_val = this->board[x][y]; // get max value present on board
            if(this->board[x][y] == 0) board_has_free_tile = true; // check if there is still a free tile
        }
    }
    if(max_val >= 2048) return {true, "You Reached 2048! Congratulations!"};
    else if(board_has_free_tile) return {false, ""};
    else if(!board_has_free_tile) return {true, "No more free tiles, try again"};
    else return {true, "Something terribly wrong has happened in GameStatus(), cancelling the game"};
}

void GameBoard::PrintHeader(){
    std::cout << "======================================" << std::endl;
    std::cout << "WELCOME TO THE GAME 2048" << std::endl;
    std::cout << std::endl;
    std::cout << "Move with 'w', 'a', 's' and 'd' followed by 'ENTER'" << std::endl;
    std::cout << std::endl;
    std::cout << "======================================" << std::endl;
}

