// File: game.cpp
// Name: Sassan Hashemi
// Date: March 19, 2018


#ifndef GAME_CPP
#define GAME_CPP


#include <iostream>
#include <cstdlib>
#include <cassert>
#include "game.h"
#include <vector>



// BOARD MEMBER FUNCTIONS
Board::Board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		_board[i] = EMPTY;
	}
	_status = IN_PROGRESS;
}
int Board::getSquare(int square) const {
	assert(square >= 0 && square < BOARD_SIZE);
	return _board[square];
}
void Board::setSquare(int square, int player) {
	assert(square >= 0 && square < BOARD_SIZE);
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
	std::cout << 1 << " | " << 2 << " | " << 3 << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << 4 << " | " << 5 << " | " << 6 << std::endl;
	std::cout << "---------" << std::endl;
	std::cout << 7 << " | " << 8 << " | " << 9 << std::endl;
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
	} else {
		_status = IN_PROGRESS;
	}
}
int Board::getBestMove(int player) {
	return minimax(*this, 0, player)[0];
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



// MINIMAX ALGORITHM
std::vector<int> minimax(Board& board, int depth, int player) {
	if (board.getStatus() == DRAW) {
		std::vector<int> result;
		result.push_back(-1);
		result.push_back(0);
		return result;
	} else if (board.getStatus() == X) {
		std::vector<int> result;
		result.push_back(-1);
		result.push_back(-10+depth);
		return result;
	} else if (board.getStatus() == O) {
		std::vector<int> result;
		result.push_back(-1);
		result.push_back(10-depth);
		return result;
	}

	if (player == X) {
		std::vector<int> bestMove;
		bestMove.push_back(-1);
		bestMove.push_back(20);
		for (int i=0; i<BOARD_SIZE; i++) {
			if (board.isEmpty(i)) {
				board.setSquare(i, X);
				board.updateStatus();
				int score = minimax(board, depth+1, O)[1];
				if (score <= bestMove[1]) {
					bestMove[1] = score;
					bestMove[0] = i;
				}
				board.setSquare(i, EMPTY);
				board.updateStatus();
			}
		}
		return bestMove;
	} else if (player == O) {
		std::vector<int> bestMove;
		bestMove.push_back(-1);
		bestMove.push_back(-20);
		for (int i=0; i<BOARD_SIZE; i++) {
			if (board.isEmpty(i)) {
				board.setSquare(i, O);
				board.updateStatus();
				int score = minimax(board, depth+1, X)[1];
				if (score >= bestMove[1]) {
					bestMove[1] = score;
					bestMove[0] = i;
				}
				board.setSquare(i, EMPTY);
				board.updateStatus();
			}
		}
		return bestMove;
	}
	std::cerr << "Shouldn't get to the end of the minimax function" << std::endl;
	exit(1);
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
			_gameMode = DRAW;
			break;
		case 'X':
		case 'x':
			_gameMode = X;
			break;
		case 'O':
		case 'o':
			_gameMode = O;
			break;
		default:
			std::cout << "Invalid choice, please try again" << std::endl;
			selectGameMode();
	}
}
void Game::play() {
	switch (_gameMode) {
		case DRAW:
			playHuman();
			break;
		case X:
			playAI(X);
			break;
		case O:
			playAI(O);
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
		takeTurnHuman(X);
		if (_board.getStatus() == EMPTY) {
			takeTurnHuman(O);
		}
	}

	printEndGame();
}
void Game::playAI(int player) {
	std::cout << "Welcome to TicTacToe. The board is shown below with each " <<
	"square represented by the number it contains. To play a move, type in " <<
	"the number of the square you wish to play in, and press enter." << 
	std::endl;

	_board.printSquareNumbers();
	if (player == X) {
		while (_board.getStatus() == EMPTY) {
			takeTurnHuman(X);
			if (_board.getStatus() == EMPTY) {
				takeTurnAI(O);
			}
		}
	} else if (player == O) {
		while (_board.getStatus() == EMPTY) {
			takeTurnAI(X);
			if (_board.getStatus() == EMPTY) {
				takeTurnHuman(O);
			}
		}
	}
	
	printEndGame();
}
void Game::takeTurnHuman(int player) {
	assert(player == X || player == O);
	int square;
	std::cout << "Please enter the number of the square you wish to play in: ";
	std::cin >> square;
	while (square<1  || square>9 || !_board.isEmpty(square-1)) {
		std::cout << "Invalid choice, please try again" << std::endl;
		std::cout << "Please enter the number of the square you wish to play in: ";
		std::cin >> square;
	}

	_board.setSquare(square-1, player);
	_board.updateStatus();
	_board.printBoard();
}
void Game::takeTurnAI(int player) {
	int move = _board.getBestMove(player);
	_board.setSquare(move, player);
	_board.updateStatus();
	std::cout << "The AI played in the square " << move+1 << std::endl;
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

















