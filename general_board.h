#include <iostream>
#include <vector>


#ifndef GENERAL_BOARD_H

using namespace std;


typedef int Move;
typedef int player;

class GeneralBoard {
protected:
  int player_turn;
  int no_players;
  bool game_over;

public:
  virtual vector<Move> getAvailableMoves(player a_player) = 0;
  virtual player getWinner()= 0;
  virtual bool isGameOver() = 0;
  virtual bool doMove(Move a_move) = 0;
  virtual void printBoard() = 0;
  virtual player getPlayerTurn() = 0;
  //virtual GeneralBoard cloneBoard() = 0; // to be implemented with template in the future
};



#define GENERAL_BOARD_H
#endif
