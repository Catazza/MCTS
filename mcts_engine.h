#include <iostream>
#include <vector>
#include "tree_node.h"
#include "connect_four_board.h"

using namespace std;


class MCTSEngine {
private:
  int max_iterations;
  double max_time;
  static const double Cp;
  TreeNode* descendTree(TreeNode* a_node);
  TreeNode* expandTree(TreeNode* a_node);
  TreeNode* selectBestChild(TreeNode* a_node);
  double doRandomPlayout(TreeNode* a_node);
  void backupNegamax(TreeNode* a_node, double a_reward);

public:
  MCTSEngine();
  move calculateMove(GeneralBoard* a_board);

};
