#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <memory>
#include "tree_node.h"
#include "connect_four_board.h"
#include "mcts_engine.h"


using namespace std;

const double MCTSEngine :: Cp = (1/sqrt(2));


/* Constructor */
MCTSEngine :: MCTSEngine() : max_iterations(100000), max_time(-1) {
}




/* Function to descend the tree to the most urgent expandable node */
TreeNode* MCTSEngine :: descendTree(TreeNode* tree_node, mt19937_64& random_engine, 
				    ConnectFourBoard* current_game_state) {

  /* Check if non terminal node */
  while (!tree_node->isTerminal()) {

    /* Check if node is fully expanded */
    if (tree_node->hasUntriedChildren()) {
      return expandTree(tree_node, random_engine, current_game_state);   //expand the tree
    }
    else {
      tree_node = selectBestChild(tree_node);   //descend down the tree
    }
  }

  return tree_node;
} 
/* END OF FUNCTION DEFINITION */




/* Function that takes a non-fully-expanded tree node and add one of the 
   unexpanded children to the tree. */
TreeNode* MCTSEngine :: expandTree(TreeNode* a_node, mt19937_64& random_engine,
				   ConnectFourBoard* current_game_state) {
  
  /* Select which child to extend at random. */
  Move expanding_move = selectExpandingMove(a_node, random_engine); 
  
  /* Do the move */
  current_game_state->doMove(expanding_move);

  /* Create the child and move to it */
  a_node = a_node->addChild(expanding_move, current_game_state);

  return a_node;
}
/* END OF FUNCTION DEFINITION */




/* CONSIDER ASSIGNING THIS FUNCTION TO THE NODE (as Petter does) TO AVOID PASSING VECTOR OF MOVES AROUND?? */
Move MCTSEngine :: selectExpandingMove(TreeNode* a_node, mt19937_64& random_engine) {

  /* Retrieve the untried moves */
  vector<Move> available_moves = a_node->getUntriedChildren();
  
  /* Generate uniform random number */
  uniform_int_distribution<size_t> moves_distribution(0, available_moves.size() - 1);

  return available_moves[moves_distribution(random_engine)];  
} 
/* END OF FUNCTION DEFINITION */





// check max_UCT_score can be initialized to -999999
// check transition this to TreeNode instead of here for efficiency
TreeNode* MCTSEngine :: selectBestChild(TreeNode* a_node) {

  TreeNode* best_child = NULL;
  double max_UCT_score = -9999999999999;
  double UCT_score;
  vector<TreeNode*> visited_children = a_node->getVisitedChildren();

  for (TreeNode* child : visited_children) {
    UCT_score = double(child->getWins()) / double(child->getVisits()) +
      Cp * sqrt(2.0 * log(double(a_node->getVisits())) / child->getVisits());
    
    if (UCT_score > max_UCT_score){
      best_child = child;
      max_UCT_score = UCT_score;
    }
  }

  return best_child;
  //	return *max_element(children.begin(), children.end(),
  //[](TreeNode* a, TreeNode* b) { return a->UCT_score < b->UCT_score; });
}




// Different from Petter. Insted of trying, retrieves set of available moves */
double MCTSEngine :: doRandomPlayout(TreeNode* a_node, ConnectFourBoard& a_state, 
				     mt19937_64& random_engine, const player& moving_player) {
  
  /* Retrieve the untried moves */
  vector<Move> available_moves = a_state.getAvailableMoves(0);
  
  /* Generate uniform random number */
  uniform_int_distribution<size_t> moves_distribution(0, available_moves.size() - 1);

  while (!a_state.isGameOver()) {
    a_state.doMove(available_moves[moves_distribution(random_engine)]);  
    available_moves = a_state.getAvailableMoves(0); //re-fetch new set of available moves
  }

  // We are at the final state, get payoff
  if (a_state.getWinner() == 9) {
    return -0.5;  //use 0.5 for draw
  }
  else if (a_state.getWinner() == moving_player) {
    return -1.0; //moving player wins
  }
  
  return 0; // it is a lost game
}





void MCTSEngine :: backupNegamax(TreeNode* a_node, double a_reward){
  while (a_node != nullptr) {
    a_node -> updateVisits();
    a_node -> updateWins(a_reward);
    a_reward = a_reward * (-1); //invert payoff, negamax version
    a_node = a_node->getParent();
  }
}




Move MCTSEngine :: selectBestMoveRoot(TreeNode* the_root) {
  Move best_child = -1;
  double max_score = -9999999999999;
  double score;
  vector<TreeNode*> visited_children = the_root->getVisitedChildren();

  for (TreeNode* child : visited_children) {
    score = double(child->getWins()) / double(child->getVisits());
    
    if (score > max_score){
      best_child = child->getLandingMove();
      max_score = score;
    }
  }

  return best_child;
}




/* Algorithm to calculate the move the AI performs */
Move MCTSEngine :: calculateMove(ConnectFourBoard* a_board) {
  
  /* Create root of the MC Tree, starting from current state */
  TreeNode* root_tree = new TreeNode(a_board);
  //unique_ptr<TreeNode> root_tree = unique_ptr<TreeNode>(new TreeNode(a_board));  // evaluate usefulness of unique_ptr
  int moving_player = a_board->getPlayerTurn();


  /* Initialize the random-number engine */
  random_device rd;
  mt19937_64 random_engine(1997);    // Non-deterministic seed

  
  /* Backbone of the algorithm */
  for (int iter = 0; iter < max_iterations; iter++){

    /* Create a copy of the state that can be altered with moves */
    ConnectFourBoard usable_state;    //TO BE CHANGED WITH A TEMPLATE
    usable_state.cloneBoard(a_board);
    //unique_ptr<TreeNode> node = root_tree.get();

    /* Descend to the most urgent expandable node (uses UCT) */
    TreeNode* expandable_node = descendTree(root_tree, random_engine, &usable_state);

    /* Do a ramdom playout till end of game */
    double payoff = doRandomPlayout(expandable_node, usable_state, random_engine, moving_player);

    /* Back-propagate the result of the simulation */
    backupNegamax(expandable_node, payoff);
  }

  return selectBestMoveRoot(root_tree);
}
