/*
 * Game.h
 *
 *  Created on: 21 ���� 2019
 *      Author: Rubit
 */

#ifndef GAME_H_
#define GAME_H_
#define ROW 3
#define COL 3
/*
 * we have two structs- the Board struct, and the cell struct. the cell is used in the Board struct and we use both
 * of then for the game.
 * in the game module we have all the functions that are relevant for the game board itself, as we will explain later.
 */
typedef struct {
	int value;
	int fixed;
	int options[ROW*COL];
	int numOfOptions;
} Cell;
typedef struct {
	Cell **board;
	int isSolved;
}Board;
enum Command {
	SET, HINT, VALIDATE, RESTART, EXIT
};

void intializeBoard();
/*
 * checks if the value in row,col is a valid value for our game board
 */
int valid(Board *b , int row, int col);
/*
 * Initialize the array of possible options for values in position row,col to all zeros
 */
void clearOptions(Board *b, int row, int col);
/*
 * deletes the option in position index
 */
void update(Board *b,int row,int col, int index);
/*
 * gets an instance of Board and initializes the board's fields
 */
int intializeEmptyBoard(Board* b);
/*
 * gets a Board and frees the memory allocated to the board field in the Board struct
 */
void freeCellsInBoard(Board *b);
/*
 * sets the value in position row,col to the value that was given
 */
void set(int x, int y, int z, Board *b);
/*
 * returns 1 if all the cells are filled with integers that are not 0
 */
int gameOver(Board *b) ;
/*
* gets the command and calls the function of that command
*/
void commandExecution(enum Command command, int x, int y, int z, Board *b,Board *solvedBoard);
/*
 * gives a hint to the value of the board in position row,col
 */
void hint(int x,int y, Board *b, Board *solvedBoard);
/*
 * prints whether or not the current board is solvable using backtraking
 */
void validate(Board *b, Board *solvedBoard);
/*
 * copies the fields of the game board to the copy board
 */
void copyBoard(Board *gameBoard, Board* copy);
/*
 * starts the game again, by creating a new game board and solveboard
 */
void restart(Board *gameBoard, Board *solvedBoard);
/*
 * frees memory and exiting the program
 */
void Exit(Board *gameBoard, Board *solvedBoard);


/*
 * getters and setters
 */

/*
 * gets value in position row,col
 */
int getValue(Board *b, int row, int col);
/*
 * sets the value in position row,col to val
 */
void setValue(Board *b, int row, int col,int val);
/*
 * gets the number of possible options for values for position row,col
 */
int getNumOfOptions(Board *b, int row, int col);
/*
 * adds a new option, val, to the options for position row,col
 */
void addOptions(Board *b, int row, int col, int val);
/*
 * sets the number of options for position row,col to num
 */
void setNumOfOptions(Board *b, int row, int col, int num);
/*
 * gets the n-th option for position row,col (n = index)
 */
int getOptionInIndex(Board *b, int row, int col, int index);
/*
 * returns 1 is position row,col is fixes. ow 0.
 */
int isFixed(Board *b, int row, int col);
/*
 * if i =1 - sets position row,col to be fixed. if i=0 - sets position row,col to be not fixed
 */
void setFixed(Board* b,int row,int col,int i);
#endif /* GAME_H_ */
