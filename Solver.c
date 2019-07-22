/*
 * Solver.c
 *
 *  Created on: 27 ���� 2019
 *      Author: Rubit
 */
#include "Game.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "SPBufferset.h"
/*
 * #include "SPBufferset.h"
 * #include "MainAux.h"
 */


/*
 * tries possible values, from 1 to 9. If we reached 9, there is no other integer we can try.
 * Otherwise, we increment the value and check if it valid it's valid for our board
 */
int putValidInput(Board *b, int row, int col) {
    do {
        if (getValue(b, row, col) == 9) {
            setValue(b, row, col, 0);
            return 0;
        }
        setValue(b, row, col, getValue(b, row, col) + 1);

    } while (!valid(b, row, col));
    return 1;

}

/*
 * return 1 if there is a valid value for the cell (and puts the value in the cell). otherwise returns 0
 */

int putRandValidInput(Board *b, int row, int col) {
    int randIndex = 0;
    int i=0;
    /*
     * if the curr value is 0, it means we've reached a new cell, so we compute our options for this cell
     */
    if ((getValue(b, row, col)) == 0) {
        clearOptions(b, row, col);
        for ( i = 0; i < ROW * COL; i++) {
            setValue(b, row, col, i + 1);
            if (valid(b, row, col)) {
                addOptions(b, row, col, i + 1);
                setNumOfOptions(b, row, col, getNumOfOptions(b, row, col) + 1);
            }
        }
    }
    /*
     * if there are no options - we clear the cell (setting the value to 0) and return 0
     */
    if (getNumOfOptions(b, row, col) == 0) {
        setValue(b, row, col, 0);
        return 0;
    }
    /*
     * if there's only 1 option- we will choose it (not using rand())
     */
    if (getNumOfOptions(b, row, col) != 1) {
        randIndex = rand() % getNumOfOptions(b, row, col);
    }
    /*
     * otherwise, randomly choose an index and set the cell to the value in options[index]. return 1
     */
    setValue(b, row, col, getOptionInIndex(b, row, col, randIndex));
    update(b, row, col, randIndex);
    setNumOfOptions(b, row, col, getNumOfOptions(b, row, col) - 1);

    return 1;
}

/*
 * tries to fill the board with valid input using the deter/rand function declared above.
 */
int backTracking(Board *b, int row, int col, int (*checkAndUpdate)(Board *b, int row, int col)) {
    int i = ROW * COL;
    int nextRow=0, nextCol=0;

    if (row == i) {
        return 1;
    }

    nextRow = col == i - 1 ? row + 1 : row;
    nextCol = col == i - 1 ? 0 : col + 1;

    if (getValue(b,row,col)!=0) {
        return backTracking(b, nextRow, nextCol, (*checkAndUpdate));
    } else {
        while (checkAndUpdate(b, row, col)) {
            if(backTracking(b, nextRow, nextCol, (*checkAndUpdate))){
                return 1;
            }
        }
        return 0;
    }
}

void clearBoardOfCells(Board *b) {
    int i=0,j=0;
    for ( i = 0; i < ROW * COL; i++) {
        for ( j = 0; j < ROW * COL; j++) {
            setValue(b,i,j,0);
            setFixed(b,i,j,0);
        }
    }
}

/*
 * randomly choose cells to fill and fills them with random valid input
 */
void puzzleGenerator(Board *solvedBoard, Board *gameBoard, int numOfFixedCells) {

    int x=0;
    int y=0;
    int counter = 0;
    clearBoardOfCells(solvedBoard);
    clearBoardOfCells(gameBoard);
    backTracking(solvedBoard, 0, 0, putRandValidInput);
    while (counter < numOfFixedCells) {
        x = rand() % (ROW * COL);
        y = rand() % (ROW * COL);
        if (isFixed(gameBoard,y,x)) {
            continue;
        }
        setValue(gameBoard,y,x,getValue(solvedBoard,y,x));
        setFixed(gameBoard,y,x,1);
        counter += 1;
    }
}

