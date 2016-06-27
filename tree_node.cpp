#include <iostream>
#include <vector>
#include <cassert>
#include "connect_four_board.h"
#include "tree_node.h"

using namespace std;


TreeNode :: TreeNode(GeneralBoard* a_board) : games_played(0), games_won(0), untried_children(a_board->getAvailableMoves(0)), parent(nullptr), landing_move(-1), player_turn(a_board->getPlayerTurn()), is_terminal(a_board->isGameOver()) {
}


TreeNode :: TreeNode(ConnectFourBoard* a_board, Move landing_move, TreeNode* the_parent) : games_played(0), games_won(0), untried_children(a_board->getAvailableMoves(0)), parent(the_parent), landing_move(landing_move), player_turn(a_board->getPlayerTurn()), is_terminal(a_board->isGameOver()) {

}


bool TreeNode :: hasUntriedChildren(){
  return ! untried_children.empty();
}



// check put const Move& ??
TreeNode* TreeNode :: addChild(Move _landing_move, ConnectFourBoard* a_state){

  /* Create the new child */
  TreeNode* node = new TreeNode(a_state, _landing_move, this);

  /* Add it to the list of visited children */
  visited_children.push_back(node);
  
  //assert (! visited_children.empty());

  /* remove it from the list of untried children */
  auto itr = untried_children.begin();
  for (; itr != untried_children.end() && *itr != _landing_move; ++itr);
  //attest(itr != moves.end());

  /* Now itr points to the ex untried child to delete */
  untried_children.erase(itr);
  
  return node;
}




bool TreeNode :: isTerminal() {
  return is_terminal;
}


vector<Move> TreeNode :: getUntriedChildren() {
  return untried_children;
}



vector<TreeNode*> TreeNode :: getVisitedChildren(){
  return visited_children;
}



int TreeNode :: getWins(){
  return games_won;
}



int TreeNode :: getVisits(){
  return games_played;
}


void TreeNode :: updateWins(double a_payoff){
  games_won += a_payoff;
}


void TreeNode :: updateVisits(){
  games_played += 1;
}



TreeNode* TreeNode :: getParent(){
  return parent;
}


Move TreeNode :: getLandingMove(){
  return landing_move;
}
