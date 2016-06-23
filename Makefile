connectFour: connect_four_main.o connect_four_board.o mcts_engine.o tree_node.o
	g++ -Wall -g connect_four_main.o connect_four_board.o mcts_engine.o tree_node.o -o connectFour

connect_four_main.o: connect_four_main.cpp connect_four_board.h
	g++ -Wall -g -c connect_four_main.cpp


connect_four_board.o: connect_four_board.cpp connect_four_board.h general_board.h
	g++ -Wall -g -c connect_four_board.cpp


mcts_engine.o: mcts_engine.cpp mcts_engine.h
	g++ -Wall -g -c mcts_engine.cpp


tree_node.o: tree_node.cpp tree_node.h
	g++ -Wall -g -c tree_node.cpp


clean_o: 
	rm -f *.o connectFour
