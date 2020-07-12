#ifndef PAWN_HPP
#define PAWN_HPP
class Pawn{
private:
  enum TYPE{MEN,KING};
  enum STATUS{ON_BOARD,BEATEN};
  enum PLAYER{P1, P2};

  TYPE type;
  STATUS status;
  PLAYER player;

public:
  Pawn(int n);
  void changeType();
  void changeStatus();
  void setPlayer(int n);
  void move(int tile);
  bool isOnBoard();

  int getIntStatus();
  int getIntType();
  int getIntPlayer();
};
#endif
