#include "inc/Pawn.hpp"

Pawn::Pawn(int n){
  setPlayer(n);
  status = ON_BOARD;
  type = MEN;
}

void Pawn::setPlayer(int n){
  if(n == 1) player = P1;
  else player = P2;
}

void Pawn::changeType(){
  if(type == MEN) type = KING;
  else type = MEN;
}

void Pawn::changeStatus(){
  if(status == ON_BOARD) status = BEATEN;
  else status = ON_BOARD;
}

int Pawn::getIntType(){
  if(type == MEN) return 0;
  else return 1;
}

int Pawn::getIntStatus(){
  if(status != ON_BOARD) return 0;
  else return 1;
}

int Pawn::getIntPlayer(){
  if(player == P1) return 1;
  else return 2;
}

bool Pawn::isOnBoard(){
  if(status == ON_BOARD) return true;
  else return false;
}
