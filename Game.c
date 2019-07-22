/*
 * Game.c
 *
 *  Created on: 21 במאי 2019
 *      Author: Rubit
 */
/*
 * free memory
 * check that calloc works every time we use it
 */
#include <stdio.h>
/*
 * #include "Game.h"
 */
#include <stdlib.h>
#include <string.h>
#include "SPBufferset.h"
#include "MainAux.h"
#include "Solver.h"
#include "Parser.h"
/*
 * checks if the value in row,col is a valid value for our game board
 */
int valid(Board *b, int row, int col) {
	Cell **board = (*b).board;
	int i=0,j=0,startRow=0,startCol=0;

	int value = board[row][col].value;
	/*
	 * makes sure that the value doesn't exists in row
	 */
	for (i = 0; i < ROW * COL; i++) {
		if (i != col && board[row][i].value == value) {
			return 0;
		}
	}

	/*
	 * makes sure that the value doesn't exists in col
	 */
	for (j = 0; j < ROW * COL; j++) {
		if (j != row && board[j][col].value == value) {
			return 0;
		}
	}

	startRow = row - row % ROW;
	startCol = col - col % COL;
	/*
	 * makes sure that the value doesn't exists in square
	 */
	for ( i = startRow; i < startRow + ROW; i++) {
		for ( j = startCol; j < startCol + COL; j++) {
			if (i != row && j != col && board[i][j].value == value) {
				return 0;
			}
		}
	}

	return 1;

}


/*
 * Initialize the array of possible options for values in position row,col to all zeros
 */
void clearOptions(Board *b, int row, int col) {
    int i=0;
	for ( i = 0; i < ROW * COL; i++) {
		(*b).board[row][col].options[i] = 0;
	}
	(*b).board[row][col].numOfOptions = 0;

}

/*
 * deletes the option in position index
 */
void update(Board *b, int row, int col, int index) {
    int i=0;
	for ( i = index + 1; i < ROW * COL; i++) {
		(*b).board[row][col].options[i - 1] = (*b).board[row][col].options[i];
	}
}


int intializeEmptyBoard(Board* b) {
	Cell **cells = (Cell**) calloc(ROW * COL, sizeof(Cell*));
	int i =0;
	int j =0;
	b->isSolved =0;
	if(callocFailed("createEmptyBoard", cells)){
		free(cells);
		return 0;

	}
	for ( i = 0; i < ROW * COL; i++) {
		cells[i] = (Cell*) calloc(ROW * COL, sizeof(Cell));
		if(callocFailed("createEmptyBoard", cells[i])){
			for( j = 0; j <= i ; j++){
				free(cells[j]);

			}
			free(cells);
			return 0;
		}

	}
	/*
	 * initializing the cell's fields (except the options,witch is initialized in clearOptions function)
	 */
	for(i=0;i<ROW*COL;i++){
	    for(j=0;j<ROW*COL;j++){
	        cells[i][j].value =0;
	        cells[i][j].fixed = 0;
	    }
	}
	(*b).board = cells;
	return 1;
}
void freeCellsInBoard(Board *b) {
    int i =0;
	for ( i = 0; i < ROW * COL; i++) {
		free((*b).board[i]);
	}
	free((*b).board);
}


/*
 * gets the command and calls the function of that command
 */
void commandExecution(enum Command command, int x, int y, int z,
		Board *gameBoard, Board *solvedBoard) {
	switch (command) {
	case SET:
		set(x, y, z, gameBoard);
		break;
	case HINT:
		hint(x, y, gameBoard, solvedBoard);
		break;
	case VALIDATE:
		validate(gameBoard, solvedBoard);
		break;
	case RESTART:
		restart(gameBoard, solvedBoard);
		break;
	case EXIT:
		Exit(gameBoard, solvedBoard);
		break;
	}
}

/*
 * returns 1 if all the cells are filled with integers that are not 0
 */
int gameOver(Board *gameBoard) {
    int i =0;
    int j=0;
	for ( i = 0; i < ROW * COL; i++) {
		for ( j = 0; j < ROW * COL; j++) {
			if ((*gameBoard).board[i][j].value == 0) {
				return 0;
			}
		}
	}
	(*gameBoard).isSolved = 1;
	return 1;
}

/*
 * sets the value in position row,col to the value that was given
 */
void set(int x, int y, int z, Board *gameBoard) {
	int orginalValue = (*gameBoard).board[x][y].value;
	SP_BUFF_SET()
	;
	/*
	 * if the game is solved- set is an invalid command and we will return an error
	 */
	if ((*gameBoard).isSolved) {
		ErrorPrinting(INVALIDCOMMAND, "set");
		return;
	}

	if ((*gameBoard).board[x][y].fixed) {
		ErrorPrinting(FIXEDCELL, "set");
		return;
	}
	(*gameBoard).board[x][y].value = z;
	if (z == 0) {
		printBoard(gameBoard);
		return;
	}
	/*
	 * if the new value is invalid, we will set the value back to what it was before and return an error
	 */
	if (!valid(gameBoard, x, y)) {
		ErrorPrinting(INVALIDVALUE, "set");
		(*gameBoard).board[x][y].value = orginalValue;
		return;
	}
	/*
	 * if the new value is not 0, we need to check if it completed our board
	 */
	printBoard(gameBoard);
	if (gameOver(gameBoard)) {
		printf("Puzzle solved successfully\n");
	}
	return;
}
void hint(int x, int y, Board *gameBoard, Board *solvedBoard) {
	SP_BUFF_SET()
	;
	if ((*gameBoard).isSolved) {
		ErrorPrinting(INVALIDCOMMAND, "set");
		return;
	}
	printf("Hint: set cell to %d\n", (*solvedBoard).board[x][y].value);
}
/*
 * prints whether or not the current board is solvable using backtraking
 */
void validate(Board *gameBoard, Board *solvedBoard) {
	Board* copy;
	SP_BUFF_SET()
	;
	if ((*gameBoard).isSolved) {
		ErrorPrinting(INVALIDCOMMAND, "set");
		return;
	}
	/*
	 * creating a new copy of the board, which will be with the same values of the game board,
	 *  but with fixed cells (so that our back tracking algorithm will work)
	 */
	copy = (Board*) calloc(1, sizeof(Board));
	intializeEmptyBoard(copy);
	copyBoard(gameBoard, copy);

	/*
	 * checks if the board is solvable, frees memory
	 */
	if (backTracking(copy, 0, 0, putValidInput) == 0) {
		printf("Validation failed: board is unsolvable\n");
		freeCellsInBoard(copy);
		free(copy);
	} else {
		freeCellsInBoard(solvedBoard);
		(*solvedBoard).board = (*copy).board;
		free(copy);
		printf("Validation passed: board is solvable\n");

	}
}

void copyBoard(Board *gameBoard, Board* copy) {
    int i=0;
    int j =0;
	for ( i = 0; i < ROW * COL; i++) {
		for ( j = 0; j < ROW * COL; j++) {
			(*copy).board[i][j].value = (*gameBoard).board[i][j].value;
		}
	}
    (*copy).isSolved = (*gameBoard).isSolved;
}
void restart(Board *gameBoard, Board *solvedBoard) {
    int numOfFixedCells = initializeGame(gameBoard,solvedBoard);
	(*gameBoard).isSolved = 0;
	puzzleGenerator(solvedBoard, gameBoard, numOfFixedCells);
    printBoard(gameBoard);
    getCommands(gameBoard, solvedBoard);
}
/*
 * frees memory and exiting the program
 */
void Exit(Board *gameBoard, Board *solvedBoard) {
	SP_BUFF_SET();
	printf("Exiting...\n");
	freeCellsInBoard(gameBoard);
	freeCellsInBoard(solvedBoard);
	free(gameBoard);
	free(solvedBoard);
	exit(0);

}







/*
 * getters and setters
 */
int getValue(Board *b, int row, int col) {
	return ((*b).board)[row][col].value;
}
void setValue(Board *b, int row, int col, int val) {
	(*b).board[row][col].value = val;
}

int getNumOfOptions(Board *b, int row, int col) {
	return (*b).board[row][col].numOfOptions;
}
void addOptions(Board *b, int row, int col, int val) {
	int numOfop = (*b).board[row][col].numOfOptions;
	(*b).board[row][col].options[numOfop] = val;
}
void setNumOfOptions(Board *b, int row, int col, int num) {
	(*b).board[row][col].numOfOptions = num;
}

int getOptionInIndex(Board *b, int row, int col, int index) {
	return (*b).board[row][col].options[index];
}

int isFixed(Board *b, int row, int col) {
	return (*b).board[row][col].fixed;
}
void setFixed(Board* b,int row,int col, int i) {
    (*b).board[row][col].fixed = i;
}




