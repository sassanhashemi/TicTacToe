game: game.cpp game.o main.cpp
	g++ -g -Wall game.cpp game.h -c game.o
	g++ game.o main.cpp -o game

#tests: game.cpp game.o tests.cpp
#	g++ -g -Wall game.cpp game.h -c game.o
#	g++ game.o tests.cpp -o tests

clean:
	rm game tests game.h.gch *.o