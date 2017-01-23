#ifndef C4_H
#define C4_H
#include <stdio.h>
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

int colsAvailable(char board[6][7]);

int spacesAvailable(char board[6][7]);

int spacesAvailableIn(char board[6][7], int col);

bool isTie(char board[6][7]);

char winner(char board[6][7]);

char opponent(char token);

void addPiece(char board[6][7], int loc, char token);

void removePiece(char board[6][7], int loc);


int char2col(char loc);

char col2char(int loc);

int evaulateBoard(char board[6][7], char player, char token);

int has3of4(char q[4], char player);

int canBeForced(char board[6][7], int row, int col, char turn, char player);

#endif
