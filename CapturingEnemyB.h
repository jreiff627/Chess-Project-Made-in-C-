#include <ctype.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8
int blackScore = 0;
int countB = 0;
int scoreCheckB(){
  return blackScore;
}

void capturingEnemyB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                     int destRow, int destCol) {
  char enemyPiece = board[destRow][destCol];
  switch (enemyPiece) {

  case 'p':
    blackScore = blackScore + 1; // whitepawn
    enemyPiece = ' ';
    break;

  case 'r': // white rook
    blackScore = blackScore + 5;
    enemyPiece = ' ';
    break;

  case 'n': // white knight
    blackScore = blackScore + 3;
    enemyPiece = ' ';
    break;

  case 'b': // white bishop
    blackScore = blackScore + 3;
    enemyPiece = ' ';
    break;

  case 'q': // white queen
    blackScore = blackScore + 9;
    enemyPiece = ' ';
    break;

  case 'k': // white king
    break;
  }
  printf("\n Piece was captured. Black Score: %d\n", blackScore);
}




