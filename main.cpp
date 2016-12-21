#include <iostream>
#include "c4.h"

typedef struct {
	int move;
	int score;
} AI_Move;

player choosePlayer();
char human(char board[6][7], char token);
int minimax(char board[6][7], char player, char token);
char bestMove(char board[6][7], char token);
char nextAvailable(char board[6][7], char token);

int main(int argc, char ** argv){
	player player1 = bestMove;
	player player2 = bestMove;
	
	playGame(player1, player2);
	
	return 0;
	
}

player choosePlayer(){
	return human;
}

char human(char board[6][7], char token){
	char loc;
	cout << "enter the letter of the column you would like to drop in, " << token << "\n";
	cin >> loc;
	return loc;
}


char bestMove(char board[6][7], char token){

	int bestScore = -1000;
	int bestC = nextAvailable(board, token);
	
	for (int c = 0; c < 7; c++){
		if (!isAvailable(board, c)) continue;
		printf("trying column %d\n", c);
		// there is room in this column
		addPiece(board, c, token);
		// get the value of this board:
		int score = minimax(board, token, opponent(token));
		// We got the score, so the board can be put back
		removePiece(board, c);
		
		if (score > bestScore){
				bestScore = score;
				bestC = c;
		}
		
	}
	printf("I choose to put a piece in column %c\n", col2char(bestC));
	return col2char(bestC);
}

int minimax(char board[6][7], char player, char token){
	char win = winner(board);
	// if the original player is currently going, they look for the best score
	// so anything >=0 will replace -10000. If its the opponent's turn, anything should
	// be less than 10000
	int bestScore = (player == token)?-10000:10000;
	
	// Base cases: check the values of the board. If terminal, return it's value
	if (win == player) return 10;
	if (win == opponent(player)) return -10;
	if (isTie(board)) return 0;
	
	// If not terminal, return the minimax values of the possible boards
	for (int c = 0; c < 7; c++){
		int score;
		if (!isAvailable(board, c)){
//			printf("Column %d is full\n", c);
			continue;
		}
		// there is room in this column
		addPiece(board, c, token);
		// get the value of this board:
		score = minimax(board, player, opponent(token));
		// We got the score, so the board can be put back
		removePiece(board, c);
		
		
		
		// see if it's a best
		if (player == token){
		
			if (score > bestScore){
				bestScore = score;
			}
		}
		else {
			if (score < bestScore){
				bestScore = score;
			}
		}
		
	}
	
	return bestScore;
	
}


char nextAvailable(char board[6][7], char token){
	for(int c = 0; c < 7; c++){
		if (isAvailable(board, c)) return col2char(c);
	}
	
	return col2char(-1);

}

