#include "inc/Player.hpp"
#include <iostream>

#define BOARD_SIZE 10

Player::Player(Board& b,int number){
  board = b;
  player = number;
}

bool Player::move(int fromTile,int toTile){
  if(isPlayerPawn(fromTile)){
    if(isMoveCorrect(fromTile,toTile)){
      if(board.getTiles().at(toTile)->getPawnPlayer() != 0 && board.getTiles().at(toTile)->getPawnPlayer() != player)
        board.getTiles().at(toTile)->getPawn()->changeStatus();
      board.getTiles().at(toTile)->setPawn(board.getTiles().at(fromTile)->getPawn());
      board.getTiles().at(fromTile)->setPawn(nullptr);
  }
    return true;
  }
 return false;
}

bool Player::isPlayerPawn(int tile){
  if(board.getTiles().at(tile)->getPawn()){
    if(board.getTiles().at(tile)->getPawn()->getIntPlayer() == player){
      return true;
    }
  }
  return false;
}

bool Player::isMovePossible(int toTile){
  int multiplicator = 0;

  if(toTile % 10 == 0 || (toTile + 1) % 10) return false;
  if((toTile > 0 && toTile < 9) || (toTile < 99 &&  toTile > 80)) return false;

  if(player == 1) multiplicator = 1;
  else(player == 2) multiplicator = -1;

  possibleMove1 = toTile + 10*multiplicator + 1;
  possibleMove2 = toTile + 10*multiplicator - 1;

  if(tiles.at(possibleMove1)->getPawnPlayer() == 0 || tiles.at(possibleMove2)->getPawnPlayer() == 0)
}

bool Player::isMoveCorrect(int fromTile, int toTile){

  if(board.getTiles().at(toTile)->getPawnPlayer() == player) return false;

  if(fromTile % BOARD_SIZE == 0){
    switch(player){
      case 1: //when player 1(up) moves from tile on the first row
        if(toTile == fromTile + 11) return true;
        else return false;
        break;
      default: //when player 2(down) moves from tile on the first row
        if(toTile == fromTile - 9) return true;
        else return false;
        break;
    }
  }
  else if((fromTile + 1) % 10 == 0){
    switch (player) {
      case 1:
        if(toTile == fromTile + 9) return true;
        else return false;
        break;
      default:
        if(toTile == fromTile - 11) return true;
        else return false;
        break;
    }
  }
  else{
    switch (player) {
      case 1:
        if(toTile == fromTile + 9 || toTile == fromTile + 11) return true;
        else return false;
        break;
      default:
        if(toTile == fromTile - 11 || toTile == fromTile - 9) return true;
        else return false;
      break;
    }
  }
}

bool Player::hasToCapture(){
  std::map<int, int> status = board.status();
  int multiplicator = 0;
  int possibleMove = 0;
  if(player == 1) multiplicator = 1;
  else multiplicator = -1;
  for(std::map<int,int>::iterator it = status.begin() ; it != status.end(); ++it){
    if(it->second == player){
      if(it->first % 10 == 0){
        possibleMove = tiles.at(it + 10 * multiplicator + multiplicator)->getPawnPlayer();
        if(possibleMove != player && possibleMove != 0 && isMovePossible(it->first,possibleMove)){

        }
      }
    }
  }

}
