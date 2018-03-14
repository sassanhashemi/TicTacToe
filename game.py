#from player import *

#from neuralnet import *

"""COMPLETE"""

import numpy as np

X = 0
O = 1

class Board:

	def __init__(self):
		self.value = np.array([[-1, -1, -1],
							   [-1, -1, -1],
							   [-1, -1, -1]])
		self.didXWin = False
		self.didOWin = False
		self.isTie = False

	def getSquareValue(self, square):
		if self.value[int(square)//3][int(square)%3] == X:
			return 'X'
		elif self.value[int(square)//3][int(square)%3] == O:
			return 'O'
		return self.value[int(square)//3][int(square)%3]

	def getSquare(self, square):
		return self.value[int(square)//3][int(square)%3]

	def isSquareEmpty(self, square):
		if self.getSquare(square) == X or self.getSquare(square) == O:
			return False
		return True

	def isBoardEmpty(self):

		for i in range(9):
			if not self.isSquareEmpty(i):
				return False
		return True

	def isBoardFull(self):
		for i in range(9):
			if self.isSquareEmpty(i):
				return False
		return True

	def updateGameStatus(self):
		"""Did X win?"""
		if self.getSquare(0) == self.getSquare(1) == self.getSquare(2) == X or \
		   self.getSquare(3) == self.getSquare(4) == self.getSquare(5) == X or \
		   self.getSquare(6) == self.getSquare(7) == self.getSquare(8) == X or \
		   self.getSquare(0) == self.getSquare(3) == self.getSquare(6) == X or \
		   self.getSquare(1) == self.getSquare(4) == self.getSquare(7) == X or \
		   self.getSquare(2) == self.getSquare(5) == self.getSquare(8) == X or \
		   self.getSquare(0) == self.getSquare(4) == self.getSquare(8) == X or \
		   self.getSquare(2) == self.getSquare(4) == self.getSquare(6) == X:
			self.didXWin = True

		"""Did O win?"""
		if self.getSquare(0) == self.getSquare(1) == self.getSquare(2) == O or \
		   self.getSquare(3) == self.getSquare(4) == self.getSquare(5) == O or \
		   self.getSquare(6) == self.getSquare(7) == self.getSquare(8) == O or \
		   self.getSquare(0) == self.getSquare(3) == self.getSquare(6) == O or \
		   self.getSquare(1) == self.getSquare(4) == self.getSquare(7) == O or \
		   self.getSquare(2) == self.getSquare(5) == self.getSquare(8) == O or \
		   self.getSquare(0) == self.getSquare(4) == self.getSquare(8) == O or \
		   self.getSquare(2) == self.getSquare(4) == self.getSquare(6) == O:
			self.didOWin = True

		"""Is the game a tie?"""
		if self.isBoardFull() and not self.didXWin and not self.didOWin:
			self.isTie = True

	def isGameOver(self):
		if self.didXWin or self.didOWin or self.isTie:
			return True
		return False

	def placePiece(self, square, piece):
		self.value[int(square)//3][int(square)%3] = piece

	def removePiece(self, square):
		self.value[int(square)//3][int(square)%3] = -1

	def possibleMoves(self):
		result = []
		for i in range(9):
			if self.isSquareEmpty(i):
				result.append(i)
		return result

	def minimax(self, player, depth=0):
		if player == O:
			best = -10
		else:
			best = 10

		if self.isGameOver():
			if self.didXWin:
				return -10 + depth, None
			elif self.didOWin:
				return 10 - depth, None
			elif self.isTie:
				return 0, None

		bestMove= -1

		for move in self.possibleMoves():
			self.placePiece(move, player)
			val, temp = self.minimax(1-player, depth+1)
			self.removePiece(move)
			if player == O:
				if val > best:
					best, bestMove = val, move
			elif player == X:
				if val < best:
					best, bestMove = val, move

		return best, bestMove





#Human vs Human play functions
def printBoard(board):
	newBoard = []
	for square in range(9):
		if board.getSquare(square) == X or board.getSquare(square) == O:
			newBoard += board.getSquareValue(square)
		else:
			newBoard += " "

	print(newBoard[0], " | ", newBoard[1], " | ", newBoard[2])
	print("-------------")
	print(newBoard[3], " | ", newBoard[4], " | ", newBoard[5])
	print("-------------")
	print(newBoard[6], " | ", newBoard[7], " | ", newBoard[8])

def printRawBoard(board):
	print(board.getSquare(0), " | ", board.getSquare(1), " | ", board.getSquare(2))
	print("-------------")
	print(board.getSquare(3), " | ", board.getSquare(4), " | ", board.getSquare(5))
	print("-------------")
	print(board.getSquare(6), " | ", board.getSquare(7), " | ", board.getSquare(8))

def printNumbersBoard():
	print(0, " | ", 1, " | ", 2)
	print("-------------")
	print(3, " | ", 4, " | ", 5)
	print("-------------")
	print(6, " | ", 7, " | ", 8)

def playX(board):
	printBoard(board)
	square = int(input("Player one (X), select which square you would like to play in: "))
	if board.isSquareEmpty(square):
		board.placePiece(square, X)
	else:
		board.didOWin = True

def playO(board):
	printBoard(board)
	square = int(input("Player two (O), select which square you would like to play in: "))
	if board.isSquareEmpty(square):
		board.placePiece(square, O)
	else:
		board.didXWin = True

def runTwoPlayers():
	board = Board()
	printNumbersBoard()

	while True:
		if not board.isGameOver():
			playX(board)
			board.updateGameStatus()
		if not board.isGameOver():
			playO(board)
			board.updateGameStatus()
		if board.isGameOver():
			break

	if board.didXWin:
		print("Player 1 wins!")
	elif board.didOWin:
		print("Player 2 wins!")
	elif board.isTie:
		print("It's a tie!")

	if board.isGameOver():
		print("Game over")



#AI vs AI play functions
def playXAI(board, square):
	if board.isSquareEmpty(square):
		board.placePiece(square, X)
	else:
		board.didOWin = True

def playOAI(board, square):
	if board.isSquareEmpty(square):
		board.placePiece(square, O)
	else:
		board.didXWin = True

def playAI():
	board = Board()
	moves = np.array([])

	while True:
		if not board.isGameOver():
			playXAI(board)
			board.updateGameStatus()
		if not board.isGameOver():
			playO(board)
			board.updateGameStatus()
		if board.isGameOver():
			break
