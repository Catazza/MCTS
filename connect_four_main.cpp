#include <iostream>
#include <random>
#include "general_board.h"
#include "connect_four_board.h"
#include "tree_node.h"
#include "mcts_engine.h"


using namespace std;


int main(){
  
  Move a_move;
  ConnectFourBoard the_board;

  the_board.printBoard();
  
  while (!the_board.isGameOver()){
    cout << "Enter a move: " ;
    cin >> a_move;
    if (cin.fail()){
      cerr << "Not an integer. Please try again" << endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
    else {
      if(the_board.doMove(a_move))
	the_board.printBoard();
    }
  }


  return 0;

}
