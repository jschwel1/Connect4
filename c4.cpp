#include "c4.h"
#include <stdio.h>
#include <iostream>

/*
[row][col]
50 51 52 53 54 55 56
40 41 42 43 44 45 46
30 31 32 33 34 35 36
20 21 22 23 24 25 26
10 11 12 13 14 15 16
00 01 02 03 04 05 06



*/



// more functions
void drawBoard(char board[6][7]){
	
	printf("|---+---+---+---+---+---+---|\n");
	printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5],board[5][6]);
	printf("|---+---+---+---+---+---+---|\n");
	printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[4][0], board[4][1], board[4][2], board[4][3], board[4][4], board[4][5],board[4][6]);
	printf("|---+---+---+---+---+---+---|\n");
	printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5],board[3][6]);
	printf("|---+---+---+---+---+---+---|\n");
	printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5],board[2][6]);
	printf("|---+---+---+---+---+---+---|\n");
	printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5],board[1][6]);
	printf("|---+---+---+---+---+---+---|\n");
	printf("| %c | %c | %c | %c | %c | %c | %c |\n", board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5],board[0][6]);
	printf("|---+---+---+---+---+---+---|\n");
	printf("  a   b   c   d   e   f   g \n");

	
}

// 
void playGame(player player1, player player2){
	char token;
	char empty = ' ';
	char board [6][7]= {
						{empty, empty, empty, empty, empty, empty, empty},
						{empty, empty, empty, empty, empty, empty, empty},
						{empty, empty, empty, empty, empty, empty, empty},
						{empty, empty, empty, empty, empty, empty, empty},
						{empty, empty, empty, empty, empty, empty, empty},
						{empty, empty, empty, empty, empty, empty, empty},				
					};
/*					
	char board [6][7]= {
						{'-', 'x', '+', '-', empty, empty, empty,},
						{'a', '-', '+', '-', empty, empty, empty,},
						{'-', 'x', '+', empty, empty, empty, empty},
						{'a', '-', '/', empty, empty, empty, empty},
						{'-', 'x', '+', empty, empty, empty, empty},
						{'a', '-', '+', empty, empty, empty, empty},				
					};

	char board [6][7]= {
						{'X', 'O', 'X', 'O', 'X', empty, empty},
						{'O', 'X', 'O', 'X', 'O', empty, empty},
						{'X', 'X', 'X', 'O', empty, empty, empty},
						{'O', 'O', 'X', 'O', empty, empty, empty},
						{'X', 'O', 'X', 'X', empty, empty, empty},
						{'X', 'X', 'O', 'O', empty, empty, empty},			
					};
*/
	char loc;
	int col;
	
	
	
	for (int i = 0; i < 42; i++){
		drawBoard(board);
		if (i%2==0){
			token='X';
			loc = player1(board, token);
		}
		else{
			token = 'O';
			loc = player2(board, token);
		}
		
		col = char2col(loc);
		
		if (col < 0 || col > 6 || !isAvailable(board, col)){
			printf("The column %c is unavailable, choose another location\n", col);
			i--;
			continue;
		}
		addPiece(board, col, token);
		
		if (winner(board) != ' '){
			drawBoard(board);
			printf("Congratualation %c, you won!\n", winner(board));
			
			return;
		}
		if (isTie(board)){
			drawBoard(board);
			printf("Shucks, it's a tie\n");
			return;
		}
	
	}
}

bool isAvailable(char board[6][7], int loc){
//	printf("Board at [5][%d] is '%c';\n", loc, board[5][loc]);
	if (board[5][loc] == ' ') return true;
	return false;

}

int colsAvailable(char board[6][7]){
	int num = 0;
	for (int c = 0; c < 7; c++){
		if (isAvailable(board, c)) num++;
	}
	
	return num;
}


bool isTie(char board[6][7]){
	for (int c = 0; c < 7; c++){
		if(isAvailable(board, c)) return false;
	}
	return true;
}

char winner(char board[6][7]){
	char win;
	// check horizontal
	for (int r = 0; r < 6; r++){
		for (int c = 0; c < 4; c++){
			if (board[r][c] != ' ' && board[r][c] == board[r][c+1] && board[r][c] == board[r][c+2] && board[r][c] == board[r][c+3]){
//				printf("============Horizontal win @ r=%d\n",r);
				win = board[r][c];

				return win;
			}
		}
	}
	
	// check vertical
	for (int c = 0; c < 7; c++){
		for (int r = 0; r < 3; r++){
			if (board[r][c] != ' ' && board[r][c] == board[r+1][c] && board[r][c] == board[r+2][c] && board[r][c] == board[r+3][c]){
//				printf("============vertical win @ c = %d\n", c);
				win = board[r][c];

				return win;
			}
		}
	}
	
	// check diagonal (\)
	for (int r = 0; r < 3; r++){
		for (int c = 3; c < 7; c++){
			if (board[r][c] != ' ' && board[r][c] == board[r+1][c-1] && board[r][c] == board[r+2][c-2] && board[r][c] == board[r+3][c-3]){
//				printf("============Diagonal win \\\n");
				win = board[r][c];
				return win;
			}
		}
	}
	
	// check diagonal (/)
	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 4; c++){
			if (board[r][c] != ' ' && board[r][c] == board[r+1][c+1] && board[r][c] == board[r+2][c+2] && board[r][c] == board[r+3][c+3]){
//				printf("============Diagonal win /\n");
				win = board[r][c];

				return win;
			}
		}
	}
	
	return ' ';
}


char opponent(char token){
	if (token == 'X') return'O';
	else return 'X';
}


int char2col(char loc){
	switch(loc){
		case 'a':
		case 'A':
			return 0;
		case 'b':
		case 'B':
			return 1;
		case 'c':
		case 'C':
			return 2;
		case 'd':
		case 'D':
			return 3;
		case 'e':
		case 'E':
			return 4;
		case 'f':
		case 'F':
			return 5; 
		case 'g':
		case 'G':
			return 6;
		default:
			return -1;
	}
	
	return -1;
}


char col2char(int loc){
	printf("Trying to place piece at %d\n", loc);
	if (loc < 0) assert(0=="NOT A VALID CHOICE");
	return 'a'+loc;

}

void addPiece(char board[6][7], int loc, char token){

	for (int i = 0; i < 6; i++){
		if (board[i][loc] == ' '){
			board[i][loc] = token;
			return;
		}
	}
}

void removePiece(char board[6][7], int loc){
	for (int i = 5; i >= 0; i--){
		if (board[i][loc] != ' ') {
			board[i][loc] = ' ';
			return;
		}
	}
}

int spacesAvailable(char board[6][7]){
	int num = 0;

	for (int r = 0; r < 6; r++){
		for (int c = 0; c < 7; c++){
			if (board[r][c] == ' ') num++;
		}
	}
	return num;
}

int spacesAvailableIn(char board[6][7], int col){
		int num = 0;
		for (int r = 0; r < 6; r++){
			if (board[r][col] == ' ') num++;
		}
		
		return num;
}


int evaulateBoard(char board[6][7], char player, char token){
	// Find all viable 3-in a rows
	char quad[4];
	int score = 0;
	
	for (int r = 0; r < 6; r++){
		for (int c = 0; c < 4; c++){
			quad[0] = board[r][c];
			quad[1] = board[r][c+1];
			quad[2] = board[r][c+2];
			quad[3] = board[r][c+3];
			if (has3of4(quad, player)) {
				score++; // better to have 3 in a row
				// better if it can be forced
				if (canBeForced(board, r, c, player, player)) score+=5;
			}
			else if (has3of4(quad, opponent(player))){
				score--; // bad if opponent has three in a row
				// worse if it can be forced
				if (canBeForced(board, r, c, player, opponent(player))) score-=5;
			}
		}
	}
	
	// check vertical
	for (int c = 0; c < 7; c++){
		for (int r = 0; r < 3; r++){
			quad[0] = board[r][c];
			quad[1] = board[r+1][c];
			quad[2] = board[r+2][c];
			quad[3] = board[r+3][c];
			if (has3of4(quad, player)) {
				score++; // better to have 3 in a row
				// better if it can be forced
				if (canBeForced(board, r, c, player, player)) score+=5;
			}
			else if (has3of4(quad, opponent(player))){
				score--; // bad if opponent has three in a row
				// worse if it can be forced
				if (canBeForced(board, r, c, player, opponent(player))) score-=5;
			}
		}
	}
	
	// check diagonal (\)
	for (int r = 0; r < 3; r++){
		for (int c = 3; c < 7; c++){
			quad[0] = board[r][c];
			quad[1] = board[r+1][c-1];
			quad[2] = board[r+2][c-2];
			quad[3] = board[r+3][c-3];
			if (has3of4(quad, player)) {
				score++; // better to have 3 in a row
				// better if it can be forced
				if (canBeForced(board, r, c, player, player)) score+=5;
			}
			else if (has3of4(quad, opponent(player))){
				score--; // bad if opponent has three in a row
				// worse if it can be forced
				if (canBeForced(board, r, c, player, opponent(player))) score-=5;
			}
			
		}
	}
	
	// check diagonal (/)
	for (int r = 0; r < 3; r++){
		for (int c = 0; c < 4; c++){
			quad[0] = board[r][c];
			quad[1] = board[r+1][c+1];
			quad[2] = board[r+2][c+2];
			quad[3] = board[r+3][c+3];
			if (has3of4(quad, player)) {
				score++; // better to have 3 in a row
				// better if it can be forced
				if (canBeForced(board, r, c, player, player)) score+=5;
			}
			else if (has3of4(quad, opponent(player))){
				score--; // bad if opponent has three in a row
				// worse if it can be forced
				if (canBeForced(board, r, c, player, opponent(player))) score-=5;
			}
		}
	}
	return score;
}
int has3of4(char q[4], char player){
		int counter = 0; 
		for (int i = 0; i < 4; i++){
			if (q[i] == player) counter++;
			else if (q[i] == ' ') {}
			else counter--;
		}
		
		if (counter == 3) return 1;
		return 0;
		
}


// If it's "turn"s turn, can player be forced to put a piece there
int canBeForced(char board[6][7], int row, int col, char turn, char player){
	int numFreeNotInCol = 0;
	int numFree;
	
	for (int i = 0; i < 7; i++){
		if (i != col) numFreeNotInCol = spacesAvailableIn(board, col);
	}
	numFree = numFreeNotInCol + (row+1);
	
	if (player == turn){
		if (numFree%2 == 1) return 1;
		else return 0;
	}
	else {
		if (numFree%2 == 1) return 0;
		else return 1;
	}
	
}
