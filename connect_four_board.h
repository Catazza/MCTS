#include <iostream>
#include <vector>
#include "general_board.h"


#ifndef CONNECT_FOUR_BOARD_H


using namespace std;


class ConnectFourBoard : public GeneralBoard {
private:
  char board[6][7];
  int num_rows;
  int num_cols;
  move last_played_row;
  move last_played_col;
  player winner;
  static const char player_markers[3];
  bool checkInput(const move& a_move);
  bool checkPlayer();

public:
  ConnectFourBoard();
  virtual vector<move> getAvailableMoves(player a_player);
  virtual player getWinner();
  virtual bool checkEndgame();
  virtual bool isGameOver();
  virtual bool doMove(move a_move);
  virtual void printBoard();
  virtual player getPlayerTurn();
};




#define CONNECT_FOUR_BOARD_H
#endif
