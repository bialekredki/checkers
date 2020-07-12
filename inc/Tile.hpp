#ifndef TILE_HPP
#define TILE_HPP

#include "inc/Pawn.hpp"

class Tile{
private:
  Pawn* pawn;

public:
  Tile(int n);
  ~Tile();
  void changeStatus(int status);
  bool isOccupied();
  int whichPlayerOccupies();
  Pawn* getPawn();
  void setPawn(Pawn* pawn);
  int getPawnPlayer();
  bool checkIfPawnOnBoard();
};

#endif
