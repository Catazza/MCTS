#include <iostream>
#include <vector>
#include "connect_four_board.h"

using namespace std;

#ifndef TREE_NODE_H


class TreeNode {
private:
  int games_played;
  int games_won;
  vector<move> untried_children;
  vector<move> visited_children;
  TreeNode* parent;
  move landing_move;
  int player_turn;

public:
  TreeNode(GeneralBoard* a_board);
  TreeNode(GeneralBoard* a_board, move landing_move, TreeNode* the_parent);
  bool hasUntriedChildren();
  TreeNode* addChild();
};



#define TREE_NODE_H
#endif
