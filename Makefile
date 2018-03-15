all: game.cpp game.o main.cpp
	g++ game.o main.cpp -o tictactoe

game: game.cpp game.o
	g++ -g -Wall game.cpp game.h -c game.o

clean:
	rm tictactoe *.o