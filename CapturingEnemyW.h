#include <ctype.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8
int whiteScore = 0;
int countW =0;

int scoreCheckW(){
  return whiteScore;
}


void capturingEnemyW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                     int destRow, int destCol) {
  char enemyPiece = board[destRow][destCol];
  switch (enemyPiece) {

  case 'P':
    whiteScore = whiteScore + 1; // black pawn
    enemyPiece = ' ';
    break;

  case 'R': // black rook
    whiteScore = whiteScore + 5;
    enemyPiece = ' ';
    break;

  case 'N': // black knight
    whiteScore = whiteScore + 3;
    enemyPiece = ' ';
    break;

  case 'B': // black bishop
    whiteScore = whiteScore + 3;
    enemyPiece = ' ';
    break;

  case 'Q': // black queen
    whiteScore = whiteScore + 9;
    enemyPiece = ' ';
    break;

  case 'K': // black king
    break;
  }
  printf("\nPiece was captured. White Score: %d\n", whiteScore);
  // char message[] = "Piece was captured.";
  // popup(message);
  
}


