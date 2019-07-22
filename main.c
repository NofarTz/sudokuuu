#include "Parser.h"
#include "Game.h"
#include "Solver.h"
#include <stdlib.h>
#include "SPBufferset.h"
#include "MainAux.h"
/*
 * #include <stdio.h>
 * #include <string.h>
 * #include <time.h>
 */




int main(int argc, char *argv[]) {
    Board* gameBoard;
    Board* solvedBoard;
	int seed = atoi(argv[1])+argc-argc;
	int numOfFixedCells;
	srand(seed);
	solvedBoard = (Board*) calloc(1, sizeof(Board));
	if (callocFailed("main", solvedBoard)) {
		free(solvedBoard);
		exit(0);
	}

	gameBoard = (Board*) calloc(1, sizeof(Board));
	if (callocFailed("main", gameBoard)) {
		free(solvedBoard);
		free(gameBoard);
		exit(0);
	}
	if ((!intializeEmptyBoard(solvedBoard)) || (!intializeEmptyBoard(gameBoard))) {
		free(solvedBoard);
		free(gameBoard);
		exit(0);
	}

	numOfFixedCells = initializeGame(gameBoard, solvedBoard);
	puzzleGenerator(solvedBoard, gameBoard, numOfFixedCells);
	printBoard(gameBoard);
	getCommands(gameBoard, solvedBoard);




	freeCellsInBoard(gameBoard);
	freeCellsInBoard(solvedBoard);

	free(solvedBoard);
	free(gameBoard);
    return 1;
}

