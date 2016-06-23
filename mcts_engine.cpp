#include <iostream>
#include <vector>
#include <cmath>
#include "tree_node.h"
#include "connect_four_board.h"
#include "mcts_engine.h"



const double MCTSEngine :: Cp = (1/sqrt(2));


/* Constructor */
MCTSEngine :: MCTSEngine() : max_iterations(100000), max_time(-1){
}



TreeNode* MCTSEngine :: descendTree(TreeNode* a_node) {

} 



TreeNode* MCTSEngine :: expandTree(TreeNode* a_node) {

}



TreeNode* MCTSEngine :: selectBestChild(TreeNode* a_node) {
}



double MCTSEngine :: doRandomPlayout(TreeNode* a_node) {
}



void MCTSEngine :: backupNegamax(TreeNode* a_node, double a_reward){

}



move MCTSEngine :: calculateMove(GeneralBoard* a_board) {
  
  // create root of the MC Tree
  TreeNode* root_tree = new TreeNode(a_board);
  
  // Backbone of the algorithm
  for (int iter = 0; iter < max_iterations; iter++){
    TreeNode* expandable_node = descendTree(root_tree);
    double payoff = doRandomPlayout(expandable_node);
    backupNegamax(expandable_node, payoff);
  }

  



}
