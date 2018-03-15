
#ifndef GAME_CPP
#define GAME_CPP


#include <iostream>
#include <cstdlib>
#include <cassert>
#include "game.h"



// BOARD MEMBER FUNCTIONS
Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		_board[i] = EMPTY;
	}
	_status = IN_PROGRESS;
	_turn = X;
}
int Board::getSquare(int square) const {
	assert(square >= 0 && square < BOARD_SIZE);
	return _board[square];
}
void Board::setSquare(int square, int player) {
	assert(square >= 0 && square < BOARD_SIZE);
	assert(player == X || player == O || player == EMPTY);
	_board[square] = player;
}
bool Board::isEmpty(int square) const {
	assert(square >= 0 && square < BOARD_SIZE);
	return (_board[square] == EMPTY);
}
void Board::printBoard() const {
	std::cout << squareToPiece(0) << " | " << squareToPiece(1) << " | " << squareToPiece(2) << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << squareToPiece(3) << " | " << squareToPiece(4) << " | " << squareToPiece(5) << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << squareToPiece(6) << " | " << squareToPiece(7) << " | " << squareToPiece(8) << std::endl;
}
void Board::printSquareNumbers() const {
	std::cout << 0 << " | " << 1 << " | " << 2 << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << 3 << " | " << 4 << " | " << 5 << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << 6 << " | " << 7 << " | " << 8 << std::endl;
}
int Board::getStatus() const {
	return _status;
}
void Board::updateStatus() {
	if ((getSquare(0) == getSquare(1) && getSquare(0) == getSquare(2) && getSquare(0) == X) ||
		(getSquare(3) == getSquare(4) && getSquare(3) == getSquare(5) && getSquare(3) == X) ||
		(getSquare(6) == getSquare(7) && getSquare(6) == getSquare(8) && getSquare(6) == X) ||
		(getSquare(0) == getSquare(3) && getSquare(0) == getSquare(6) && getSquare(0) == X) ||
		(getSquare(1) == getSquare(4) && getSquare(1) == getSquare(7) && getSquare(1) == X) ||
		(getSquare(2) == getSquare(5) && getSquare(2) == getSquare(8) && getSquare(2) == X) ||
		(getSquare(0) == getSquare(4) && getSquare(0) == getSquare(8) && getSquare(0) == X) ||
		(getSquare(2) == getSquare(4) && getSquare(2) == getSquare(6) && getSquare(2) == X)) {
			_status = X;
			return;
	} else if ((getSquare(0) == getSquare(1) && getSquare(0) == getSquare(2) && getSquare(0) == O) ||
		(getSquare(3) == getSquare(4) && getSquare(3) == getSquare(5) && getSquare(3) == O) ||
		(getSquare(6) == getSquare(7) && getSquare(6) == getSquare(8) && getSquare(6) == O) ||
		(getSquare(0) == getSquare(3) && getSquare(0) == getSquare(6) && getSquare(0) == O) ||
		(getSquare(1) == getSquare(4) && getSquare(1) == getSquare(7) && getSquare(1) == O) ||
		(getSquare(2) == getSquare(5) && getSquare(2) == getSquare(8) && getSquare(2) == O) ||
		(getSquare(0) == getSquare(4) && getSquare(0) == getSquare(8) && getSquare(0) == O) ||
		(getSquare(2) == getSquare(4) && getSquare(2) == getSquare(6) && getSquare(2) == O)) {
			_status = O;
			return;
	} else if (isBoardFull()) {
		_status = DRAW;
		return;
	}
}
char Board::squareToPiece(int square) const {
	switch (_board[square]) {
		case -1:
			return ' ';
			break;
		case 0:
			return 'X';
			break;
		case 1:
			return 'O';
			break;
		default:
			std::cerr << "Invalid board setup" << std::endl;
			exit(1);
	}
}
bool Board::isBoardFull() const {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (_board[i] == EMPTY) {
			return false;
		}
	}
	return true;
}
int* Board::minimax(int depth, bool isMax) {
	assert(isMax == _turn);
	// X is the minimizing player, O is the maximizing player
	// Base case
	if (_status == X) {
		int* arr = new int[2];
		arr[0] = -1;
		arr[1] = -10+depth;
		return arr;
	} else if (_status == O) {
		int* arr = new int[2];
		arr[0] = -1;
		arr[1] = 10-depth;
		return arr;
	} else if (_status == DRAW) {
		int* arr = new int[2];
		arr[0] = -1;
		arr[1] = 0;
		return arr;
	}

	// Recursive case

	// X's turn
	if (_turn == X) {
		int* bestMove = new int[2];
		bestMove[0] = -1;
		bestMove[1] = 20;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (getSquare(i) == EMPTY) {
				setSquare(i, X);
				changeTurn();
				int* move = minimax(depth+1, O);
				if (move[1] > bestMove[1]) {
					bestMove[0] = i; //TODO: check this for error. I might have to make new move
					bestMove[1] = move[1];
				}
				setSquare(i, EMPTY);
				changeTurn();
			}
		}
		return bestMove;
	}
	
	// O's turn
	if (_turn == O) {
		int* bestMove = new int[2];
		bestMove[0] = -1;
		bestMove[1] = -20;
		for (int i = 0; i < BOARD_SIZE; i++) {
			if (getSquare(i) == EMPTY) {
				setSquare(i, O);
				changeTurn();
				int* move = minimax(depth+1, X);
				if (move[1] > bestMove[1]) {
					bestMove[0] = i;				//TODO: check this for error. I might have to make new move
					bestMove[1] = move[1];
				}
				setSquare(i, EMPTY);
				changeTurn();
			}
		}
		return bestMove;
	}
	return NULL;
}
int Board::getBestMove(int player) {
	assert(player == _turn);
	return minimax(0, player)[0];
}
void Board::changeTurn() {
	_turn = 1 - _turn;
}



// GAME MEMBER FUNCTIONS
Game::Game() {
	_board = Board();
}
void Game::selectGameMode() {
	char choice;
	std::cout << "Please select game mode (2 for 2 player, X for X vs AI, O for O vs AI): ";
	std::cin >> choice;
	switch (choice) {
		case '2':
			gameMode = DRAW;
			break;
		case 'X':
		case 'x':
			gameMode = X;
			break;
		case 'O':
		case 'o':
			gameMode = O;
			break;
		default:
			std::cout << "Invalid choice, please try again" << std::endl;
			selectGameMode();
	}
}
void Game::play() {
	switch (gameMode) {
		case DRAW:
			playHuman();
			break;
		case X:
			//playAIX();
			break;
		case O:
			//playAIO();
			break;
		default:
			std::cerr << "Invalid gameMode" << std::endl;
			exit(1);
			break;
	}
}
void Game::playHuman() {
	std::cout << "Welcome to TicTacToe. The board is shown below with each " <<
	"square represented by the number it contains. To play a move, type in " <<
	"the number of the square you wish to play in, and press enter." << 
	std::endl;

	_board.printSquareNumbers();

	while (_board.getStatus() == EMPTY) {
		std::cout << "The best move is: " << _board.getBestMove(X) << std::endl;
		takeTurnHuman(X);
		if (_board.getStatus() == EMPTY) {
			std::cout << "The best move is: " << _board.getBestMove(X) << std::endl;
			takeTurnHuman(O);
		}
	}

	printEndGame();
}
void Game::takeTurnHuman(int player) {
	assert(player == X || player == O);
	int square;
	std::cout << "Please enter the number of the square you wish to play in: ";
	std::cin >> square;
	while (!_board.isEmpty(square)) {
		std::cout << "Invalid choice, please try again" << std::endl;
		std::cout << "Please enter the number of the square you wish to play in: ";
		std::cin >> square;
	}

	_board.setSquare(square, player);
	_board.updateStatus();
	_board.changeTurn();
	_board.printBoard();
}
void Game::printEndGame() {
	switch (_board.getStatus()) {
		case DRAW:
			std::cout << "It's a tie!" << std::endl;
			break;
		case X:
			std::cout << "X wins!" << std::endl;
			break;
		case O:
			std::cout << "O wins!" << std::endl;
			break;
		case EMPTY:
			std::cerr << "printEndGame() was incorrectly called" << std::endl;
			exit(1);
			break;
		default:
			std::cerr << "printEndGame() was incorrectly called" << std::endl;
			exit(1);
			break;
	}
}



#endif

















