/*
 * ai.c
 *
 *  Created on: Apr 5, 2019
 *      Author: bbn
 */

#include "main.h"
#include <stdio.h>
#include <stdlib.h>

int ChessFind(int board[BOARD_SIZE][BOARD_SIZE], int deltax, int deltay, int x, int y, int color);
int SpaceFind(int board[BOARD_SIZE][BOARD_SIZE], int deltax, int deltay, int x, int y, int color);
int CalWeight(int number1_chess, int number2_chess, int number1_space, int number2_space, int color, int color_chess);

/** neighbour():
 *  para: color: the color of the chess of AI
 */
int Neighbour(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int color) {
	int chess_search[3][9]; 		// first: color | second: direction
	int space_search[3][9];
    int sum_weight;
	int delta_position[9][2] = {
			{0, 0},
			{0, 1},				// Up
			{-1, 0},			// Left
			{1, 1},				// Up Right
			{-1, 1},			// Up Left
			{0, -1}, 			// Down
			{1, 0},				// Right
			{-1, -1},			// Down Left
			{1, -1},			// Down Right
	};

	// Initialize
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 9; ++j) {
			chess_search[i][j] = 0;
			space_search[i][j] = 0;
		}
	}

	// Find all chesses and spaces
	for (int i = 1; i < 3; ++i) {			// For Color: only 1 and 2 are valid
		for(int j = 1; j < 9; ++ j) {		// For Direction: only 1 - 8
			chess_search[i][j] = ChessFind(board, delta_position[j][0], delta_position[j][1], x, y, i);
			space_search[i][j] = SpaceFind(board, delta_position[j][0], delta_position[j][1], x, y, i);
		}
	}

	// Calculate the weights of all directions
	sum_weight = 0;
	for (int i = 1; i < 5; i++) {
		sum_weight += CalWeight(chess_search[1][i], chess_search[1][i + 4], space_search[1][i], space_search[1][i + 4], color, 1);
		sum_weight += CalWeight(chess_search[2][i], chess_search[2][i + 4], space_search[2][i], space_search[2][i + 4], color, 2);
	}
	return sum_weight;
}

/** ChessFind():
 *  get the sum of chesses in the given direction
 */
int ChessFind(int board[BOARD_SIZE][BOARD_SIZE], int deltax, int deltay, int x, int y, int color) {
	int sum, x_curr, y_curr;
	x_curr = x;
	y_curr = y;
	sum = 0;

	// Update chess sum
	while ((x_curr + deltax < BOARD_SIZE) && (y_curr + deltay < BOARD_SIZE) \
			&& (x_curr + deltax >= 0) && (y_curr + deltay >= 0) && \
			(board[x_curr + deltax][y_curr + deltay] == color)) {
		sum ++;
		x_curr += deltax;
		y_curr += deltay;
	}

	return sum;
}

/** SpaceFind():
 *  get the sum of spaces in the given direction
 */
int SpaceFind(int board[BOARD_SIZE][BOARD_SIZE], int deltax, int deltay, int x, int y, int color) {
	int sum, x_curr, y_curr;
	x_curr = x;
	y_curr = y;
	sum = 0;

	// Move to space
	while ((x_curr + deltax < BOARD_SIZE) && (y_curr + deltay < BOARD_SIZE) \
				&& (x_curr + deltax >= 0) && (y_curr + deltay >= 0) && \
				(board[x_curr + deltax][y_curr + deltay] == color)) {
			x_curr += deltax;
			y_curr += deltay;
	}

	// Update space sum
	while ((x_curr + deltax < BOARD_SIZE) && (y_curr + deltay < BOARD_SIZE) \
					&& (x_curr + deltax >= 0) && (y_curr + deltay >= 0) && \
					(board[x_curr + deltax][y_curr + deltay] == CHESS_SPACE)) {
		        sum ++;
				x_curr += deltax;
				y_curr += deltay;
	}

	return sum;
}

/** CalWeight():
 *  calculate the weight of a given position in the board
 */
int CalWeight(int number1_chess, int number2_chess, int number1_space, int number2_space, int color, int color_chess) {
	int number_type;				// number_type: the chess type
	int state_rival; 				// state_rival: 1 means AI, 2 means the rival.
	int weight;

	number_type = number1_chess + number2_chess;
	if (color == color_chess) state_rival = 1;
	else state_rival = 2;

	weight = 0;

	if ((number1_space > 0) && (number2_space > 0)) {
		if (number_type == 1) {
			if (number1_space + number2_space > 2) {
				if (state_rival == 1) {
					weight = PRI_MF1;
				} else {
					weight = PRI_OF1;
				}
			}
		}
		else if (number_type == 2) {
			if (state_rival == 1) {
				weight = PRI_MF2;
			} else {
				weight = PRI_OF2;
			}
		}
		else if (number_type == 3) {
			if (state_rival == 1) {
				weight = PRI_MF3;
			} else {
				weight = PRI_OF3;
			}
		}
		else if (number_type == 4) {
			if (state_rival == 1) {
				weight = PRI_MF4;
			} else {
				weight = PRI_OF4;
			}
		}
	}
	else {
		if (number_type == 1) {
			if (number1_space + number2_space > 2) {
				if (state_rival == 1) {
					weight = PRI_ML1;
				} else {
					weight = PRI_OL1;
				}
			}
		}
		else if (number_type == 2) {
			if (number1_space + number2_space > 1) {
				if (state_rival == 1) {
					weight = PRI_ML2;
				} else {
					weight = PRI_OL2;
				}
			}
		}
		else if (number_type == 3) {
			if (number1_space + number2_space > 0) {
				if (state_rival == 1){
					weight = PRI_ML3;
				} else {
					weight = PRI_OL3;
				}
			}
		}
		else if (number_type == 4) {
			if (state_rival == 1) {
				weight = PRI_ML4;
			} else {
				weight = PRI_OL4;
			}
		}
	}

	return weight;
}















































