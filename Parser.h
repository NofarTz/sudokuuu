/*
 * Parser.h
 *
 *  Created on: 21 ���� 2019
 *      Author: Rubit
 */

#ifndef PARSER_H_
#define PARSER_H_
#include "Game.h"
/*
 * this module interacts with the user to gets the commands in the game
 */
/*
 * initializes the game by getting the users input for how many fixed cells he wants. returns the answer
 */
int initializeGame(Board *gameBoaqrd,Board *solvedBoard);
/*
 * gets the users commands and interprets them. then calls the function that will execute the command.
 */
void getCommands();
/*
 * checks if str in null (str is a part that we need for a command). if it is- prints an error of invalid command.
 */
int isNull(char *str);
#endif /* PARSER_H_ */
