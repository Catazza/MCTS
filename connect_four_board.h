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
  Move last_played_row;
  Move last_played_col;
  player winner;
  static const char player_markers[3];
  bool checkInput(const Move& a_move);
  bool checkPlayer();

public:
  ConnectFourBoard();
  virtual vector<Move> getAvailableMoves(player a_player);
  virtual player getWinner();
  virtual bool checkEndgame();
  virtual bool isGameOver();
  virtual bool doMove(Move a_move);
  virtual void printBoard();
  virtual player getPlayerTurn();
  ConnectFourBoard cloneBoard(ConnectFourBoard* a_board);
};




#define CONNECT_FOUR_BOARD_H
#endif
