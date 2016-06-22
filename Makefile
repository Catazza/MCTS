connectFour: connect_four_main.o connect_four_board.o
	g++ -Wall -g connect_four_main.o connect_four_board.o -o connectFour

connect_four_main.o: connect_four_main.cpp connect_four_board.h
	g++ -Wall -g -c connect_four_main.cpp


connect_four_board.o: connect_four_board.cpp connect_four_board.h general_board.h
	g++ -Wall -g -c connect_four_board.cpp



clean_o: 
	rm -f *.o connectFour
