/*
 * gomoku_main.c
 *
 *  Created on: Apr 5, 2019
 *      Author: bbn
 *
 *****************************************
 * Board Coordinate: (0,0) on LEFTBOTTOM *
 *****************************************
 *
 * Version: 1.1
 *
 * TODO:  We only take the current move into consideration,
 *        beacuse of which the AI cannot fully check the
 *        possibilities of lose. The next task is to simulate
 *        possible moves of the opponent for at least two
 *        rounds. In order to do that the situation of lose
 *        should be concluded so that we can use the result
 *        of the possible moves as an important judge of our
 *        current choice.
 *
 * TODO: We need to add a function to check if we have won or not.
 */

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int board[BOARD_SIZE][BOARD_SIZE];
	int state_game; 							// 1 -> win, 2 -> lose, 0 -> unknown.
	int x_move, y_move;							// chess position we are going to take
	int x_rival, y_rival;						// rival position
	int weight_move;							// current max weight
	int weight_select;							// weight calculated for a position

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = 0;
	state_game = 0;
	weight_move = -1;

	while (state_game == 0) {
		scanf("%d %d", &x_rival, &y_rival);
		board[x_rival][y_rival] = 2;

		for (int i = 0; i < BOARD_SIZE; i++){
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
		}

		board[x_move][y_move] = 1;
		weight_move = -1;

		printf("%d %d\n", x_move, y_move);
	}
}
