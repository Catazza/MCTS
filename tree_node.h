#include <iostream>
#include <vector>
#include "connect_four_board.h"

using namespace std;

#ifndef TREE_NODE_H


class TreeNode {
private:
  int games_played;
  int games_won;
  vector<Move> untried_children;
  vector<TreeNode*> visited_children;
  TreeNode* parent;
  Move landing_move;
  int player_turn;
  bool is_terminal;

public:
  TreeNode(GeneralBoard* a_board);
  TreeNode(ConnectFourBoard* a_board, Move landing_move, TreeNode* the_parent);
  bool isTerminal();
  vector<Move> getUntriedChildren();
  vector<TreeNode*> getVisitedChildren();
  int getWins();
  int getVisits();
  TreeNode* getParent();
  Move getLandingMove();
  void updateWins(double a_payoff);
  void updateVisits();
  bool hasUntriedChildren();
  TreeNode* addChild(Move _landing_move, ConnectFourBoard* a_state);
};



#define TREE_NODE_H
#endif
