#include "Game.h"
#include <stdio.h>
#include "SPBufferset.h"
#include "Parser.h"
#include <stdlib.h>
#include <string.h>
#include "MainAux.h"

int initializeGame(Board *gameBoard, Board *solvedBoard) {
	int numOfCells = 0;
	SP_BUFF_SET()
	;
	while (1) {
		printf("Please enter the number of cells to fill [0-80]:\n");
		if (scanf("%d", &numOfCells) <= 0) {
			if (feof(stdin)) {
				ErrorPrinting(FEOF,"");
				freeCellsInBoard(gameBoard);
				freeCellsInBoard(solvedBoard);

				free(solvedBoard);
				free(gameBoard);
				exit(0);
			}
		}
		if (numOfCells >= 0 && numOfCells <= 80) {
			break;
		}
		ErrorPrinting(INVALIDCELLSNUMBER, "");
	}
	return numOfCells;
}
int isNull(char *str) {
	if (str == NULL ) {
		ErrorPrinting(INVALIDCOMMAND, "");
		return 1;
	}
	return 0;
}
void getCommands(Board *gameBoard, Board *solvedBoard) {

	enum Command command;
	int i=0;
	char *x = "";
	char *y = "";
	char *z = "";
	char str[1025];
	int max = 1025;
	char* token;
	SP_BUFF_SET();
	while (fgets(str, max, stdin)) {
        i=0;
	    while(str[i] == '\r' || str[i] == '\t' ||  str[i] == ' '){
	        i+=1;
	    }
        if(str[i] == '\n'){
            continue;
        }

		token = strtok(str, " \t\r\n");

		if (isNull(token)) {
			continue;
		}
		if (!strcmp(token, "validate")) {
			command = VALIDATE;
		} else if (!strcmp(token, "restart")) {
			command = RESTART;
		} else if (!strcmp(token, "exit")) {
			command = EXIT;
		} else if(!strcmp(token, "set") || !strcmp(token, "hint")) {
			x = strtok(NULL, " \t\r\n");
			if (isNull(x)) {
				continue;
			}
			y = strtok(NULL, " \t\r\n");
			if (isNull(y)) {
				continue;
			}
			if (!strcmp(token, "set")) {
				z = strtok(NULL, " \t\r\n");
				if (isNull(z)) {
					continue;
				}
				command = SET;
			}
			if (!strcmp(token, "hint")) {
				command = HINT;
			}
		} else {
			ErrorPrinting(INVALIDCOMMAND, "");
			continue;
		}
		commandExecution(command,atoi(y)-1,atoi(x)-1,atoi(z),gameBoard,solvedBoard);

	}
    ErrorPrinting(FEOF,"");

	exit(0);
	}

