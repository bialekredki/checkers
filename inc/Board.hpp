#ifndef BOARD_HPP
#define BOARD_HPP

#include "inc/Tile.hpp"
#include <vector>
#include <map>

class Board{

private:
  std::vector<Tile*> tiles;

public:
  Board();
  ~Board();
  void console_Display();
  std::vector<Tile*> getTiles();
  bool checkIfWon(int player);
  std::map <int,int> status();

};
#endif
