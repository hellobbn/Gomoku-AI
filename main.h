/*
 * main.h
 *
 *  Created on: Apr 5, 2019
 *      Author: bbn
 */

#ifndef MAIN_H_
#define MAIN_H_

// Board Size
#define BOARD_SIZE 22

// Function for main
int Neighbour(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int color);

// Chess color
#define CHESS_SPACE 0
#define CHESS_WHITE 1
#define CHESS_BLACK 2

// Type
#define CHESS_PIECES 1
#define BLANK_SPACE 2

// Direction
#define DIRT_UP 1
#define DIRT_DOWN 5
#define DIRT_LEFT 2
#define DIRT_RIGHT 6
#define DIRT_UPRIGHT 3
#define DIRT_DOWNLEFT 7
#define DIRT_UPLEFT 4
#define DIRT_DOWNRIGHT 8

// Priority
#define PRI_OL1 1
#define PRI_ML1 2
#define PRI_OL2 3
#define PRI_ML2 4
#define PRI_OF1 20
#define PRI_MF1 21
#define PRI_OL3 100
#define PRI_ML3 101
#define PRI_OF2 110
#define PRI_MF2 111
#define PRI_OF3 1000
#define PRI_MF3 1050
#define PRI_OL4 6000
#define PRI_ML4 30001
#define PRI_OF4 5000
#define PRI_MF4 30001
#endif /* MAIN_H_ */
