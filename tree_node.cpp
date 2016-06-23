#include <iostream>
#include <vector>
#include "connect_four_board.h"
#include "tree_node.h"

using namespace std;


TreeNode :: TreeNode(GeneralBoard* a_board) : games_played(0), games_won(0), untried_children(a_board->getAvailableMoves(0)), parent(NULL), landing_move(-1), player_turn(a_board->getPlayerTurn()) {
}


TreeNode :: TreeNode(GeneralBoard* a_board, move landing_move, TreeNode* the_parent) : games_played(0), games_won(0), untried_children(a_board->getAvailableMoves(0)), parent(the_parent), landing_move(landing_move), player_turn(a_board->getPlayerTurn()) {

}


bool TreeNode :: hasUntriedChildren(){

}




TreeNode* TreeNode :: addChild() {

}
