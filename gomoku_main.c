/*
 * gomoku_main.c
 *
 *  Created on: Apr 5, 2019
 *      Author: bbn
 *
 *****************************************
 * Board Coordinate: (0,0) on LEFTBOTTOM *
 * ***************************************
 */

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int board[BOARD_SIZE][BOARD_SIZE];
	int state_game; // state_game: 1 means win, 2 means lose, 0 means unknown.
	int x_move, y_move, x_rival, y_rival, weight_move, weight_select;

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = 0;
	state_game = 0;
	weight_move = -1;

	while (state_game == 0) {
		scanf("%d %d", &x_rival, &y_rival);
		board[x_rival][y_rival] = 2;
		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++) {
				if ((board[i][j] == 0)) {
					weight_select = Neighbour(board, i, j, 1);
					if (weight_select > weight_move) {
						weight_move = weight_select;
						x_move = i;
						y_move = j;
					}
				}
			}
		board[x_move][y_move] = 1;
		weight_move = -1;
		printf("%d %d\n", x_move, y_move);
	}
}
