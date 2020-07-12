#include "inc/Board.hpp"
#include <iostream>

#define BOARD_SIZE 10

//create new Board object at the start of the game
//tiles == 0 empty tile || tile == 1 player1(up) pawn|| tile == 2 player2(down) pawn
Board::Board(){
  /*for(int i = 0; i < 64 ; i++){
    if(i < 16){
      tiles.push_back(new Tile(1));
    }
    else if(i > 47) tiles.push_back(new Tile(2));
    else tiles.push_back(new Tile(0));
  }*/
  int row = 1;
  bool isRowEven = false;
  bool isTileEven = true;
  for(int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
    isRowEven = row % 2 == 0;
    isTileEven = i % 2 == 0;
    if(row == 6 || row == 5) tiles.push_back(new Tile(0));
    else{
      if(!isRowEven && isTileEven) tiles.push_back(new Tile(0));
      else if(isRowEven && !isTileEven) tiles.push_back(new Tile(0));
      else if(isRowEven && isTileEven && row < 5) tiles.push_back(new Tile(1));
      else if(!isRowEven && !isTileEven && row < 5) tiles.push_back(new Tile(1));
      else tiles.push_back(new Tile(2));
    }
    if((i+1) % 10 == 0)
      ++row;
  }
}

//delete Board when game finishes
Board::~Board(){
}

void Board::console_Display(){
  //std:vector<Tile*>::iterator it = tiles.begin(); it != tiles.end(); ++it
  int counter = 0;
  for(const auto& x : tiles){
    if(counter == 0) std::cout << "|";
    if(!x->getPawn()) std::cout << " |";
    else{
      if(x->getPawn()->getIntPlayer() == 2) std::cout << "2|";
      else std::cout << "1|";
    }
    if(!((counter + 1) % 10)) std::cout << "\n|";
    counter++;
    //std::cout << (counter + 1) % 8 << '\n';
  }
  std::cout << "\n";
}

std::vector<Tile*> Board::getTiles(){
  return tiles;
}

bool Board::checkIfWon(int player){
  int counter = 0;
  for(const auto& tile : tiles){
    if(tile->getPawnPlayer() == player+1){
      if(!tile->checkIfPawnOnBoard()) counter++;
    }
  }
  if(counter == 20) return true;
  else return false;
}

std::map<int, int> Board::status(){
  std::map<int, int> result;
  int counter = 0;
  for(const auto& tile : tiles){
    result.insert(std::pair<int, int>(counter,tile->getPawnPlayer()));
    counter++;
  }
  return result;
}
