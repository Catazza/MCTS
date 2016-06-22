#include <iostream>
#include "general_board.h"
#include "connect_four_board.h"




using namespace std;



const char ConnectFourBoard :: player_markers[] = {'.', 'X', 'O'};

ConnectFourBoard :: ConnectFourBoard() {
  no_players = 2;
  player_turn = 1;  //Player 1 starts
  num_rows = 6;
  num_cols = 7; //Standard 6x7 board
  game_over = false;
  winner = 0;  //0 to indicate nobody has won yet
  last_played_row = -1;
  last_played_col = -1;
  
  // Initialize the board to be empty
  for (int row = 0; row < num_rows; row++){
    for (int col = 0; col < num_cols; col++){
      board[row][col] = '.';
    }
  }
}



/* Function to get the legal avaliable moves for this state of the board */
vector<move> ConnectFourBoard :: getAvailableMoves(player a_player){

}




player ConnectFourBoard :: getWinner(){
  return winner;
}



bool ConnectFourBoard :: isGameOver(){
  return game_over;
}



bool ConnectFourBoard :: checkEndgame(){
  //  if (last_col < 0) {
  //return player_markers[0];
  //}

  // We only need to check around the last piece played.
  char piece = board[last_played_row][last_played_col];

  // X X X X
  int left = 0, right = 0;
  for (int col = last_played_col - 1; col >= 0 && board[last_played_row][col] == piece; --col) left++;
  for (int col = last_played_col + 1; col < num_cols && board[last_played_row][col] == piece; ++col) right++;
  if (left + 1 + right >= 4) {
    winner = player_turn;
    game_over = true;
    return true;
  }

  // X
  // X
  // X
  // X
  int up = 0, down = 0;
  for (int row = last_played_row - 1; row >= 0 && board[row][last_played_col] == piece; --row) up++;
  for (int row = last_played_row + 1; row < num_rows && board[row][last_played_col] == piece; ++row) down++;
  if (up + 1 + down >= 4) {
    winner = player_turn;
    game_over = true;
    return true;
  }

  // X
  //  X
  //   X
  //    X
  up = 0;
  down = 0;
  for (int row = last_played_row - 1, col = last_played_col - 1; row >= 0 && col >= 0 && board[row][col] == piece; --row, --col) up++;
  for (int row = last_played_row + 1, col = last_played_col + 1; row < num_rows && col < num_cols && board[row][col] == piece; ++row, ++col) down++;
  if (up + 1 + down >= 4) {
    winner = player_turn;
    game_over = true;
    return true;
  }

  //    X
  //   X
  //  X
  // X
  up = 0;
  down = 0;
  for (int row = last_played_row + 1, col = last_played_col - 1; row < num_rows && col >= 0 && board[row][col] == piece; ++row, --col) up++;
  for (int row = last_played_row - 1, col = last_played_col + 1; row >= 0 && col < num_cols && board[row][col] == piece; --row, ++col) down++;
  if (up + 1 + down >= 4) {
    winner = player_turn;
    game_over = true;
    return true;
  }

  return false;
}




bool ConnectFourBoard :: doMove(move a_move){
}


void ConnectFourBoard :: printBoard(){
  cout << endl;
  cout << " ";

  //print header
  for (int col = 0; col < num_cols - 1; ++col) {
    cout << col << ' ';
  }
  
  //??
  cout << num_cols - 1 << endl;
  
  //Print inner board
  for (int row = 0; row < num_rows; ++row) {
    cout << "|";
    for (int col = 0; col < num_cols - 1; ++col) {
      cout << board[row][col] << ' ';
    }
    cout << board[row][num_cols - 1] << "|" << endl;
  }

  //Print frame
  cout << "+";
  for (int col = 0; col < num_cols - 1; ++col) {
    cout << "--";
  }
  cout << "-+" << endl;
  cout << player_markers[player_turn] << " to move " << endl << endl;

}


player ConnectFourBoard :: getPlayerTurn(){

}



