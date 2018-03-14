from game import *



def main():
	#game.runTwoPlayers()
	game = Board()
	game.placePiece(0, X)
	game.placePiece(1, O)
	game.placePiece(2, X)
	printBoard(game)
	print(game.minimax(X))



if __name__ == '__main__':
	main()
