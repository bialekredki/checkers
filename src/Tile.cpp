#include "inc/Tile.hpp"

Tile::Tile(int n){
  if(n != 0){pawn = new Pawn(n);}
  else pawn = nullptr;
}

Pawn* Tile::getPawn(){
  return pawn;
}

void Tile::setPawn(Pawn* pawn){
  this->pawn = pawn;
}

int Tile::getPawnPlayer(){
  if(pawn){
    if(pawn->getIntPlayer() == 1) return 1;
    else return 2;
  }
  return 0;
}

bool Tile::checkIfPawnOnBoard(){
  if(pawn){
    if(pawn->getIntStatus() == 1) return true;
    else return false;
  }
  return false;
}
