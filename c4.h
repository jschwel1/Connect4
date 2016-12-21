#ifndef C4_H
#define C4_H
#include <iostream>
#include <assert.h>

using namespace std;


//define a datatype for player functions
typedef char ((*player)(char board[6][7], char token));


// more functions
void drawBoard(char board[6][7]);

// 
void playGame(player player1, player player2);

bool isAvailable(char board[6][7] , int loc);

bool isTie(char board[6][7]);

char winner(char board[6][7]);

char opponent(char token);

void addPiece(char board[6][7], int loc, char token);

void removePiece(char board[6][7], int loc);


int char2col(char loc);

char col2char(int loc);


#endif
