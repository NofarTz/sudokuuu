/*
 * Solver.h
 *
 *  Created on: 27 ���� 2019
 *      Author: Rubit
 */

#ifndef SOLVER_H_
#define SOLVER_H_
/*
 * implements the logic behind the game. responsible for finding a possible solution for boards
 */


/*
 * tries to fill the board with valid input using the deter/rand function declared above.
 */
int backTracking(Board *b, int row, int col,int (*f)(Board *b, int row, int col));
/*
 * return 1 if there is a valid value for the cell (and puts the value in the cell). otherwise returns 0
 */
int putRandValidInput(Board *b, int row, int col);
/*
 * tries possible values, from 1 to 9. If we reached 9, there is no other integer we can try.
 * Otherwise, we increment the value and check if it valid it's valid for our board
 */
int putValidInput(Board *b, int row, int col);
/*
 * randomly choose cells to fill and fills them with random valid input
 */
void puzzleGenerator(Board *solvedBoard,Board *gameBoard,int numOfFixedCells);
#endif /* SOLVER_H_ */
