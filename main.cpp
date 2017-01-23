#include <iostream>
#include "c4.h"



player choosePlayer();
char human(char board[6][7], char token);
int minimax(char board[6][7], char player, char token);
int alphaBeta(char board[6][7], char player, char token, int ab, int depth);
char bestMove(char board[6][7], char token);
char nextAvailable(char board[6][7], char token);

int main(int argc, char ** argv){
	
	player player1 = choosePlayer();
	player player2 = choosePlayer();
	
	playGame(player1, player2);
	
	return 0;
	
}

player choosePlayer(){
	int choice;
	printf("1. Human\n");
	printf("2. Computer: Next Move\n");
	printf("3. Computer: Minimax\n");
	cin >> choice;
	
	switch(choice){
		case 1:
			return human;
		case 2:
			return nextAvailable;
		case 3:
			return bestMove;
	}
	return nextAvailable;
	
}

char human(char board[6][7], char token){
	char loc;
	cout << "enter the letter of the column you would like to drop in, " << token << "\n";
	cin >> loc;
	return loc;
}


char bestMove(char board[6][7], char token){
	//if (board[5][4] == ' ') return 'd';
	int bestScore = -1000;
	int bestC = nextAvailable(board, token);
	
	for (int c = 0; c < 7; c++){
		if (!isAvailable(board, c)) continue;

		// there is room in this column
		addPiece(board, c, token);
		// get the value of this board:
		int score = alphaBeta(board, token, opponent(token), -100000, 0);
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

int alphaBeta(char board[6][7], char player, char token, int ab, int depth){
	char win = winner(board);
	// if the original player is currently going, they look for the best score
	// so anything >=0 will replace -10000. If its the opponent's turn, anything should
	// be less than 10000
	int bestScore = (player == token)?-10000:10000;
	
	// Base cases: check the values of the board. If terminal, return it's value
	if (win == player) {
//		printf("Depth: %d\n",depth);
		return 50-depth;
	}
	else if (win == opponent(player)) {
//		printf("Depth: %d\n",depth);
		return depth-50;
	}
	else if (isTie(board)) {
//		printf("Depth: %d\n",depth);
		return 0;
	}
	
	// FIX THE DEPTH and count it as a tie for now...
	if (depth + colsAvailable(board) > 12 && token == player) {
		int temp = 0;

		temp = evaulateBoard(board, player, token);
	//	printf("Max depth reached, this board is currently worth %d\n", temp);
	
		return temp-depth;
	}


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
		score = alphaBeta(board, player, opponent(token), bestScore, depth+1);
		// We got the score, so the board can be put back
		removePiece(board, c);
		
		
		
		// see if it's a best
		// Maximizer
		if (player == token){		
			if (score > bestScore){
				bestScore = score;
			}
			if (bestScore >= ab) return bestScore;
		}
		// Minimizer
		else {
			if (score < bestScore){
				bestScore = score;
			}
			
			if (bestScore <= ab) return bestScore;
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

