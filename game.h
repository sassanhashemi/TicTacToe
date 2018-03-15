

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
		int getBestMove(int player);
		void changeTurn();



	private:
		char squareToPiece(int square) const;
		bool isBoardFull() const;
		int* minimax(int depth, bool isMax);

		int _turn;
		int _board[BOARD_SIZE];
		int _status;		//0 = X win, 1 = O win, 2 = tie, -1 = in progress
};






class Game {

	public:
		Game();
		void selectGameMode();
		void play();
	
	private:
		void playHuman();
		//void playAIX();
		//void playAIO();
		void takeTurnHuman(int player);
		//void takeTurnAI();
		void printEndGame();

		int gameMode;
		Board _board;
};



#endif