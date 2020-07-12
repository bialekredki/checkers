#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "inc/Board.hpp"
#include <map>

class Player{
private:
  Board board;
  int player;
  bool isPlayerPawn(int tile);
  bool isMoveCorrect(int fromTile, int toTile);
  boll isMovePossible(int toTile);


public:
  Player(Board& b, int number);

  bool move(int fromTile, int toTile);
  bool hasToCapture();
};

#endif
