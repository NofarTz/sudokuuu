/*
 * MainAux.h
 *
 *  Created on: 23 ���� 2019
 *      Author: Rubit
 */

#ifndef MAINAUX_H_
#define MAINAUX_H_
#include "Game.h"
/*
 * MainAux has all auxiliary functions that are relevant for the game
 */

/*
 * the implemention depends on the game moudle (cell and bpard...). can we fix it?
 */
void printBoard(Board *b);
enum Errors {
	MEMORYALLOCATION,
	INVALIDCELLSNUMBER,
	FEOF,
	FIXEDCELL,
	INVALIDVALUE,
	INVALIDCOMMAND
};
/*
 * gets an enum error and calls the right function
 */
void ErrorPrinting(enum Errors error, char fumcName[]);
/*
 * checking if calloc worked
 * we need to check this function (we dont know how)
 */
int callocFailed(char funcName[], void* arr);
#endif /* MAINAUX_H_ */
