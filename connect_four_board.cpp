#include <iostream>
#include <cctype>
#include "general_board.h"
#include "connect_four_board.h"




using namespace std;


/* Markers to fill the board */
const char ConnectFourBoard :: player_markers[] = {'.', 'X', 'O'};



/* Constructor */
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
/* END OF FUNCTION DEFINITION */




/* Function to create a copy of the current board */
ConnectFourBoard ConnectFourBoard :: cloneBoard(ConnectFourBoard* a_board) {


  for (int row = 0; row < num_rows; row++){
    for (int col = 0; col < num_cols; col++){
      board[row][col] = a_board->board[row][col];
    }
  }

  player_turn = a_board->player_turn;
  game_over = a_board->game_over;
  winner = a_board->winner;
  last_played_row = a_board->last_played_row;
  last_played_col = a_board->last_played_col;
}


/* Function to get the legal avaliable moves for this state of the board */
vector<Move> ConnectFourBoard :: getAvailableMoves(player a_player){
  checkPlayer();

  vector<Move> available_moves;

  if (game_over) {
    return available_moves;
  }

  available_moves.reserve(num_cols);

  for (int col = 0; col < num_cols; ++col) {
    if (board[0][col] == player_markers[0]) {
      available_moves.push_back(col);
    }
  }

  return available_moves;

}
/* END OF FUNCTION DEFINITION */




player ConnectFourBoard :: getWinner(){
  return winner;
}
/* END OF FUNCTION DEFINITION */



bool ConnectFourBoard :: isGameOver(){
  return game_over;
}
/* END OF FUNCTION DEFINITION */




bool ConnectFourBoard :: checkEndgame(){
  // Check - was there but possibly remove.
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
/* END OF FUNCTION DEFINITION */




/* Function to submit a move to the board. Also checks the move is valid. 
 Output: returns true if move successfully made. */
bool ConnectFourBoard :: doMove(Move a_move) {
  
  if (!checkInput(a_move)) {
    return false;
  }

  if (board[0][a_move] != player_markers[0]) {
    cerr << "column already full" << endl;
    return false;
  }
  
  if (!checkPlayer()){
    cerr << "something went wrong with player numbers"<<endl;
    return false;
  }

  if (isGameOver()){
    cerr << "Game has already ended";
    return false;
  }

  //find available spot and set it
  int row = num_rows - 1;
  while (board[row][a_move] != player_markers[0]) row--;
  board[row][a_move] = player_markers[player_turn];

  last_played_col = a_move;
  last_played_row = row;


  /* check if the move ends the game */
  if (checkEndgame()) {
    cout << "Game is over." << endl;
    cout << "Player "<< getWinner() << " wins!" << endl;
    return true;
  }

  player_turn = 3 - player_turn;  

  return true;
}
/* END OF FUNCTION DEFINITION */



/* Helper function to print te board to screen */
void ConnectFourBoard :: printBoard(){
  cout << endl;
  cout << " ";

  //print header
  for (int col = 0; col < num_cols; ++col) {
    cout << col << ' ';
  }
  cout << endl;
  

  //Print inner board
  for (int row = 0; row < num_rows; ++row) {
    cout << "|";
    for (int col = 0; col < num_cols - 1; ++col) {
      cout << board[row][col] << ' ';
    }
    cout << board[row][num_cols - 1] << "|" << endl;
  }

  //Print bottom part of frame
  cout << "+";
  for (int col = 0; col < num_cols - 1; ++col) {
    cout << "--";
  }
  cout << "-+" << endl;
  
  if (!isGameOver())
    cout << player_markers[player_turn] << " (Player " << player_turn << ")" << " to move " << endl << endl;

}
/* END OF FUNCTION DEFINITION */




/* maybe unused?? */
player ConnectFourBoard :: getPlayerTurn(){
  return player_turn;
}
/* END OF FUNCTION DEFINITION */




/* Helper function to check input is clean. To be improved for letters. modifying cin possibly */
bool ConnectFourBoard :: checkInput(const Move& a_move) {

  // Check move out of bounds
  if (a_move < 0 || a_move > 6) {
    cerr << "Move out of bounds." << endl;
    return false;
  } 

  // Check letter
  if (isalpha(a_move)) {
    cerr << "need numeric input" << endl;
    return false;
  }

  return true;
}
/* END OF FUNCTION DEFINITION */




/* Quick check to see if it's still player 1 or 2 to move */
bool ConnectFourBoard :: checkPlayer() {
  if (player_turn == 1 || player_turn == 2)
    return true;

  return false;
}
/* END OF FUNCTION DEFINITION */


