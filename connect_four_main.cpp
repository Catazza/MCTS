#include <iostream>
#include <random>
#include "general_board.h"
#include "connect_four_board.h"
#include "tree_node.h"
#include "mcts_engine.h"


using namespace std;


int main(){
  
  Move player_move;
  Move ai_move;
  ConnectFourBoard the_board;
  MCTSEngine ai_player;

  /* Show initial virgin state */
  the_board.printBoard();
  
  while (!the_board.isGameOver()){
    
    /* AI moves first */
    ai_move = ai_player.calculateMove(&the_board);
    the_board.doMove(ai_move);
    the_board.printBoard();


    /* Then the player moves */
    cout << "Enter a move: " ;
    cin >> player_move;
    if (cin.fail()){
      cerr << "Not an integer. Please try again" << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
    else {
      if(the_board.doMove(player_move))
	the_board.printBoard();
    }
  }

  /* game is over */
  cout << "Game is over." << endl;
  if (the_board.getWinner() == 9) {
    cout << "Game ended in a draw!" << endl;
  }
  else {
    cout << "Player "<< the_board.getWinner() << " wins!" << endl;
  }

  return 0;

}
