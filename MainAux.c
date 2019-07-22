/*
 * MainAux.c
 *
 *  Created on: 23 ���� 2019
 *      Author: Rubit
 */

#include "MainAux.h"
#include "Game.h"
#include "SPBufferset.h"
#include <stdlib.h>
#define ROW 3
#define COL 3
/*
 * the implemention depends on the game moudle (cell and bpard...). can we fix it?
 */
void printBoard(Board *b) {
    int i=0,row=0,col=0;
	SP_BUFF_SET()
	;
	for ( i = 0; i < 34; i++) {
		printf("-");
	}
	for ( row = 0; row < ROW * COL; row++) {
		printf("\n");
		printf("|");
		for ( col = 0; col < ROW * COL; col++) {
			printf(" ");
			if (isFixed(b, row, col)) {
				printf(".%d", getValue(b, row, col));
			} else {
				if (getValue(b, row, col) == 0) {
					printf("  ");
				} else {
					printf(" %d", getValue(b, row, col));
				}
			}
			if (col % 3 == 2) {
				printf(" |");
			}
		}
		if (row % 3 == 2) {
			printf("\n");
			for ( i = 0; i < 34; i++) {
				printf("-");
			}

		}
	}
	printf("\n");
}

/*
 * gets an enum error and calls the right function
 */
void ErrorPrinting(enum Errors error, char funcName[]) {
	SP_BUFF_SET()
	;
	switch (error) {
	case MEMORYALLOCATION:
		printf("Error: %s has failed\n", funcName);
		break;
	case INVALIDCELLSNUMBER:
		printf("Error: invalid number of cells to fill (should be between 0 and 80)\n");
		break;
	case FEOF:
		printf("Exiting...\n");

		break;
	case FIXEDCELL:
		printf("Error: cell is fixed\n");
		break;
	case INVALIDVALUE:
		printf("Error: value is invalid\n");
		break;
	case INVALIDCOMMAND:
		printf("Error: invalid command\n");
		break;
	}
}
/*
 * checking if calloc worked
 * we need to check this function (we dont know how)
 */

int callocFailed(char funcName[], void* arr) {
	if (arr == NULL ) {
		ErrorPrinting(MEMORYALLOCATION, funcName);
		return 1;
	}
	return 0;
}
