# File: Makefile
# Name: Sassan Hashemi
# Date: March 19, 2018


game: game.cpp game.h main.cpp game.o
	g++ -g -Wall game.cpp -c
	g++ game.o main.cpp -o game	


#tests: game.cpp game.o tests.cpp
#	g++ -g -Wall game.cpp game.h -c game.o
#	g++ game.o tests.cpp -o tests

clean:
	rm game *.o