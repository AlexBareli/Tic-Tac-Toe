#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

/* This is a structure that defines a Tic Tac Toe board that is 3x3 */

struct tictacboard {
	char spaces[3][3];
};

typedef char tictacboard_t[3][3];

/* The initializeboard function takes a Tic Tac Toe board as an argument, and fills the board in with '_' */

void initializeboard (tictacboard_t board) {
	int row;
	int col;

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			board[row][col] = '_';
		}
	}
}

/* The setboard function takes a Tic Tac Toe board and a char array of X's and O's as arguments, and fills the board with the specified moves */

void setboard (tictacboard_t board, char **moves) {
	int row;
	int col;
	int i = 1;

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			board[row][col] = moves[i][0];
			i++;
		}
	}
}

/* The printboard function takes a Tic Tac Toe board as an argument and prints it */

void printboard (tictacboard_t board) {
	int row;
	int col;

	for (row = 0; row < 3; row++) {
		printf(" ");
		for (col = 0; col < 3; col++) {
			if (col < 2) {
				printf("%c | ", board[row][col]);
			}
			else {
				printf("%c \n", board[row][col]);
			}
		}
		if (row < 2) {
			printf("---+---+--- \n");
		}
	}
}

/* The checkrow function takes a Tic Tac Toe board as an argument, and checks to see if any of the rows are winning rows. If there is a row that satisfies the win conditions,
the function returns 1 if the winner is 'X' and 0 if the winner is 'O' */

int checkrow (tictacboard_t board) {
	int i;

	for (int i = 0; i < 3; i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != '_') {
			if (board[i][1] == 'X') {
				return(1);
			}
			else {
				return(0);
			}
		}
	}
	return(-1);
}

/* The checkcol function takes a Tic Tac Toe board as an argument, and check to see if any of the columns are winning columns. If there is a column that satisfies the win
conditions, the function returns 1 if the winner is 'X' and 0 if the winner is 'O' */

int checkcol (tictacboard_t board) {
	int i;

	for (int i = 0; i < 3; i++) {
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != '_') {
			if (board[1][i] == 'X') {
				return(1);
			}
			else {
				return(0);
			}
		}
	}
	return(-1);
}

/* The checkdiag function takes a Tic Tac Toe board as an argument, and checks to see if any of the diagonals are winning diagonals. If there is a diagonal that satisfies the win
conditions, the function returns 1 if the winner is 'X' and 0 if the winner is 'O' */

int checkdiag (tictacboard_t board) {
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != '_') {
		if (board[1][1] == 'X') {
			return(1);
		}
		else {
			return(0);
		}
	}
	else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != '_') {
		if (board[1][1] == 'X') {
			return(1);
		}
		else {
			return(0);
		}
	}
	return(-1);
}

/* The checkdraw function takes a Tic Tac Toe board as an argument, and checks to see if the board meets draw conditions. The function will return 1 if all the spots on the
board have been populated by an X or an O, otherwise the function returns a 0 if there is still a blank space. */

int checkdraw (tictacboard_t board) {
	int row;
	int col;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row][col] == '_') {
				return(0);
			}
		}
	}
	return(1);
}

/* The function minimax is a recursive algorithm that determines the best move to make for a given player. The two players are called the Maximizer (which is 'X'), whose goal is
to make the move that gives the largest possible score and the Minimizer (which is 'O'), whose goal is to get the lowest possible score. The program loops over every empty spot
and makes a test move for the given player, then recursively calls minimax to see if this move gives the highest or lowest possible score for the Maximizer or the Minimizer. The
score is also determined by how many moves it takes for the program to win, which is substracted from the final score in order to make the optimal move possible. */

int minimax (tictacboard_t gameboard, char player, int depth) {
	int row;
	int col;

	if (checkrow(gameboard) == 0 || checkcol(gameboard) == 0 || checkdiag(gameboard) == 0 ) {
		return(-10 + depth);
	}
	if (checkrow(gameboard) == 1 || checkcol(gameboard) == 1 || checkdiag(gameboard) == 1 ) {
		return(10 - depth);
	}
	if (checkdraw(gameboard) == 1 ) {
		return(0);
	}

	if (player == 'X') {
		int score = -10;
		for (row = 0; row < 3; row++) {
			for (col = 0; col < 3; col++) {
				if (gameboard[row][col] == '_') {
					gameboard[row][col] = player;
					score = MAX(score, minimax(gameboard, 'O', depth + 1));
					gameboard[row][col] = '_';
				}
			}
		}
		return(score);
	}
	else {
		int score = 10;
		for (row = 0; row < 3; row++) {
			for (col = 0; col < 3; col++) {
				if (gameboard[row][col] == '_') {
					gameboard[row][col] = player;
					score = MIN(score, minimax(gameboard, 'X', depth + 1));
					gameboard[row][col] = '_';
				}
			}
		}
		return(score);
	}
}

/* The function find_best_move determines the best possible move to make with the help of minimax. The program takes the specified player, loops over all the empty spots making 
test moves, and calls minimax on the opponent to see if the move that was made gives the current player the best chance of winning. Once the program determines the optimal move to
make that results in the best possible score, it will return the row and column value to be used in main to make this move */


void find_best_move (tictacboard_t board, char player, int *prow, int *pcol) {
	int row;
	int col;
	int best;

	if (player == 'X') {
		best = -10;
	}
	if (player == 'O') {
		best = 10;
	}

	for (row = 0; row < 3; row++) {
		for (col = 0; col < 3; col++) {
			if (board[row][col] == '_') {
				board[row][col] = player;
				int score = minimax(board, 'X', 0);
				board[row][col] = '_';
				if (score < best) {
					best = score;
					*prow = row;
					*pcol = col;
				}
			}
		}
	}
}

/* The main function is where the Tic Tac Toe game is played. First, if the program is called without an argument then the program will enter a loop where the user will be able
to play the game against the A.I. The program loops and asks the user for an input of where they want to place X, then it checks if the board is a win or a draw for a player.
If the player hasn't won the game yet, then the program calls find_best_move to make the best possible move against the human player, and checks to see if a win for the A.I or a
draw has been reaced. The loop terminates once the player or A.I wins the game, or if the board has been populated and is a draw. The program can also take a string of X's and O's
(i.e: X O X _ X _ X O X ) to represent a partially filled in board, where the program will determine the best possible move to make for O in the given board state */

int main (int argc, char **argv) {
	tictacboard_t gameboard;

	if (argc == 1) {
		int row;
		int col;
		initializeboard(gameboard);

		while (argc == 1) {
			printboard(gameboard);
			printf("X: ");
			fscanf(stdin,"%d %d", &row, &col);
			if ((row < 3 && row > -1) && (col < 3 && col > -1) && gameboard[row][col] == '_' ) {
				gameboard[row][col] = 'X';
				if (checkcol(gameboard) == 1 || checkrow(gameboard) == 1 || checkdiag(gameboard) == 1) {
					printboard(gameboard);
					printf("X Wins! \n");
					break;
				}
				else if (checkdraw(gameboard) == 1) {
					printboard(gameboard);
					printf("Draw \n");
					break;
				}
				find_best_move(gameboard, 'O', &row, &col);
				gameboard[row][col] = 'O';
				printf("O: %d %d \n", row, col);
				if (checkcol(gameboard) == 0 || checkrow(gameboard) == 0 || checkdiag(gameboard) == 0) {
					printboard(gameboard);
					printf("O Wins! \n");
					break;
				}
				else if (checkdraw(gameboard) == 1) {
					printboard(gameboard);
					printf("Draw \n");
					break;
				}
			}
			else {
				printf("Illegal Move \n");
			}
		}
	}
	else if (argc > 2) {
		int row;
		int col;
		setboard(gameboard, argv);
		printboard(gameboard);
		find_best_move(gameboard, 'O', &row, &col);
		printf("O: %d %d \n", row, col);
	}
	return(0);
}
