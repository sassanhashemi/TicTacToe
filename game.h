

#ifndef GAME_H
#define GAME_H


const int IN_PROGRESS = -1;
const int EMPTY = IN_PROGRESS;
const int X = 0;
const int O = 1;
const int DRAW = 2;
const int BOARD_SIZE = 9;


class Board {

	public:
		
		Board();
		int getSquare(int square) const;
		void setSquare(int square, int player);
		bool isEmpty(int square) const;
		void printBoard() const;
		void printSquareNumbers() const;
		int getStatus() const;
		void updateStatus();



	private:
		char squareToPiece(int square) const;
		bool isBoardFull() const;

		int _board[BOARD_SIZE];
		int _status;		//0 = X win, 1 = O win, 2 = tie, -1 = in progress
};

std::vector<int> minimax(Board board, int depth, int player);




class Game {

	public:
		Game();
		void selectGameMode();
		void play();
	
	private:
		void playHuman();
		void playAI(int player);
		void takeTurnHuman(int player);
		void takeTurnAI(int player);
		void printEndGame();

		int gameMode;
		Board _board;
};



#endif