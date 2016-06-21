#include <iostream>
#include <vector>
#include "general_board.h"


#ifndef CONNECT_FOUR_BOARD_H


using namespace std;


class ConnectFourBoard : public GeneralBoard {
private:
  char board[7][6];

public:
  ConnectFourBoard();
  virtual vector<move> getAvailableMoves(player a_player);
  virtual player getWinner();
  virtual bool isGameOver();
  virtual bool doMove(move a_move);
  virtual void printBoard();
  virtual player getPlayerTurn();
};




#define CONNECT_FOUR_BOARD_H
#endif
