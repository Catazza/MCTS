#include <iostream>
#include <vector>
#include <random>
#include "tree_node.h"
#include "connect_four_board.h"

using namespace std;


class MCTSEngine {
private:
  int max_iterations;
  double max_time;
  static const double Cp;
  TreeNode* descendTree(TreeNode* tree_node, mt19937_64& random_engine, ConnectFourBoard* current_game_state);
  TreeNode* expandTree(TreeNode* a_node, mt19937_64& random_engine, ConnectFourBoard* current_game_state);
  TreeNode* selectBestChild(TreeNode* a_node);
  Move selectBestMoveRoot(TreeNode* the_root);
  double doRandomPlayout(TreeNode* a_node);
  void backupNegamax(TreeNode* a_node, double a_reward);
  Move selectExpandingMove(TreeNode* a_node, mt19937_64& random_engine);

public:
  MCTSEngine();
  Move calculateMove(ConnectFourBoard* a_board);

};
