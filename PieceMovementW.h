#include "CapturingEnemyW.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SpecialMovementsW.h"

#define BOARD_SIZE 8
int rookWmove = 0;
int kingWmove = 0;

void popup(const char *message) {
  initscr();
  printw(message);
  refresh();
  getch();
  endwin();
  message = " ";
}

///////PAWN MOVEMENT/////////////

int pawnmovementW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                   int destRow, int destCol) {
  // Check if Valid
  int validity = 1;

  int DeltaY = (destRow - orgRow); // Delta Y
  int DeltaX= (destCol - orgCol); // Delta X
  if (DeltaY > 0) { // Checks the path if pawn is moving backwards
    char message[] = "Invalid Move. Pawn can not move backwards."; popup(message);
    validity = 0;
  }

  if (DeltaY < -2) { // checks for the pawn to move in y direction
    char message[] = "Invalid Move. Pawn can only move one spot in the y-direction\n";  popup(message);
    validity = 0;
    
  } else if (DeltaY < -1 && orgRow !=  6) { // check
    char message[] = "Invalid Move. Pawn can only move one spot in the y-direction unless it is it's first move, or it is capturing a piece.\n";  popup(message);
    validity = 0;
  }

  if (validity == 1 && (DeltaY == 1 || DeltaY == -1) &&
      (DeltaX == 1 || DeltaX == -1)) { // trying to check if the move for
                                       // diagonal and only by one spot
    char targetPiece = board[destRow][destCol];
    char targetPiece2 = board[destRow + 1][destCol];
    if (isupper(targetPiece)) { // scanning if an enemy is present since enemy
                                // is uppercase
      printf("Capturing Enemy %d", board[destRow][destCol]);
      capturingEnemyW(board, orgRow, orgCol, destRow, destCol);
      board[destRow][destCol] = 112;
      board[orgRow][orgCol] = ' ';
      return 1;
    }
    else if (isupper(targetPiece2) && (orgRow == 3)){
      printf("EnPassant\n");
      validity = 1;
      board[destRow+1][destCol] = ' ';
      board[orgRow][orgCol] = ' ';
      board[destRow][destCol] = 112;
      ++whiteScore;
      return 1;
    }else {
      char message[] = "Invalid Move. Pawn can only move diagonally if an enemy piece is present.\n";  popup(message);
      validity = 0;
      return 0;
    }
  }
  if (validity == 1 && destRow == 0){
    char message[] = "Pawn can upgrade. Enter the letter of the piece you want to upgrade   to(FirstLetter of piece or N for knight):";  popup(message);
    char upgrade;
    scanf(" %c", &upgrade);
    upgrade = tolower(upgrade);
    while (upgrade != 'r' && upgrade != 'n' && upgrade != 'b' && upgrade != 'q'){
      printf("Invalid input. Enter the letter of the piece you want to upgrade to. First Letter of piece or N for knight"); 
      scanf(" %c", &upgrade);
      upgrade = tolower(upgrade);
      printf("You entered: %c\n", upgrade);
    }
    board[destRow][destCol] = upgrade;
    validity = 0;
    board[orgRow][orgCol] = ' ';
    return 1;
  }

  // If move is valid, update the board
  if (validity) {
    char piece = board[orgRow][orgCol];
    board[orgRow][orgCol] = ' ';
    board[destRow][destCol] = piece;
    return 1;
  }
  else {return 0;}
  
  
}

//////Knight movement///////////
int knightMovementW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                     int destRow, int destCol) {
  // I know Im making this confusing with different names, but its the only way
  // for my brain to keep track of these variables without having a brain
  // aneurysm
  int deltaX = abs(destRow - orgRow);
  int deltaY = abs(destCol - orgCol);
  int validity = 0;

  // Check if the move is an L shape
  if ((deltaX == 1 && deltaY == 2) || (deltaX == 2 && deltaY == 1)) {
    validity = 1;
  }
  // Check if the destination square is occupied by own piece
  if (islower(board[destRow][destCol])) {
    validity = 0;
  }

  // will need to check if the move is obstructed by other pieces?

  if (validity) { // once it passes all checks, move the knight
    char piece = board[orgRow][orgCol];
    board[orgRow][orgCol] = ' ';
    // Updating the piece
    board[destRow][destCol] = piece;
    return 1;
  }
  else {return 0;}
}

/////////ROOK Movement///////////
int RookMovementW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                   int destRow, int destCol) {

  int deltaX = abs(destRow - orgRow);
  int deltaY = abs(destCol - orgCol);
  int validity = 1;
  int i = orgRow;
  int j = orgCol;

  // Check if the move only in one direction, just in the X or Y only.
  if ((deltaX != deltaY) || (deltaX > 0 && deltaY == 0) ||
      (deltaX == 0 && deltaY > 0)) {
 // Check if there are any pieces in the way
    if(i > destRow){--i;}else if(i< destRow){++i;}
    if(j > destCol){--j;}else if(j<destCol){++j;;}
  while (i != destRow || j != destCol){
  if (islower(board[i][j])) {  // Check if the destination square is occupied by own piece
    validity = 0;
     char message[] = "Invalid Move. You have a piece there. ";
     popup(message);
    break;
  }
  if (isupper(board[i][j])) {
    validity = 1;
    printf("Capturing Enemy");
    capturingEnemyW(board, orgRow, orgCol, destRow, destCol);
    break;
  }
    if(i > destRow){--i;}else if(i< destRow){++i;}
    if(j > destCol){--j;}else if(j<destCol){++j;;}
  }
  }
  if (validity) { // once it passes all checks, move the rook
    char piece = board[orgRow][orgCol];
    board[orgRow][orgCol] = ' ';
    // Updating the piece
    board[destRow][destCol] = piece;
    return 1;
  }
  else {return 0;}
}
///////Bishop movement/////////
int bishopmovementW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                     int destRow, int destCol) {
  // Bishop can move at a diagonal
  // Check if Valid
  int j = orgCol;
  int i = orgRow;
  int validity = 0;
  int checkRow = abs(destRow - orgRow);
  int checkCol = abs(destCol - orgCol);
  if (i < destRow) {i = i + 1;if (j < destCol) { j = j + 1;} else {j = j - 1; } }
  else { i = i - 1;if (j < destCol) {j = j + 1;} else {j = j - 1;}}
  if (checkRow != checkCol) { // Checks the path is a diagonal
    char message[] = "Invalid Move. Bishop moves in a diagonal Line";  popup(message);
    return 0;
  }
  if (checkRow == checkCol) {
    char piece = board[i][j];
    piece = board[i][j];
    while (i != (destRow)) {
      piece = board[i][j];
      if (piece > 65 && piece < 83) {
        printf("Capturing Enemy");
        capturingEnemyW(board, orgRow, orgCol, destRow, destCol);
        validity = 1;
        break;}
      if (piece < 115 && piece > 97) {
         char message[] = "Invalid Move. You have a piece there. ";
         popup(message);
        validity = 0;
        break;
      } else {
        validity = 1;
      }
      if (i < destRow) {i = i + 1;if (j < destCol) { j = j + 1;} else {j = j - 1; } }
      else { i = i - 1;if (j < destCol) {j = j + 1;} else {j = j - 1;}}
    }
    if (i == destRow) {
      piece = board[i][j];
      if (piece > 65 && piece < 83) {
        printf("Capturing Enemy");
        capturingEnemyW(board, orgRow, orgCol, destRow, destCol);
        validity = 1;
      } else if (piece < 115 && piece > 97) {
        char message[] = "Invalid Move. You have a piece there. ";
        popup(message);
        validity = 0;
      } else {
        validity = 1;
      }
    }

    if (validity == 1) {
      char piece = board[orgRow][orgCol];
      board[orgRow][orgCol] = ' ';
      // Updating the piece
      board[i][j] = piece;
      return 1;
    }
  else {return 0;}
  }
}
//////Queen movement///////////
int QueenmovementW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                    int destRow, int destCol) {
  int deltaX = abs(destRow - orgRow);
  int deltaY = abs(destCol - orgCol);
  int complete = 0;
  // Bishop
  if (deltaX == deltaY) {
    complete = bishopmovementW(board, orgRow, orgCol, destRow, destCol);
  }
  // Rook Move
  // Check if the move only in one direction, just in the X or Y only.
  else if ((deltaX > 0 && deltaY == 0) ||(deltaX == 0 && deltaY > 0)) {
    complete = RookMovementW(board, orgRow, orgCol, destRow, destCol);
  }
  return complete;
}
//////King movement///////////  
void KingmovementW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
int destRow, int destCol) {
  int check = 0;
  
  int deltaX = abs(destCol - orgCol);
  int deltaY = abs(destRow - orgRow);
  int validity = 0;
  printf("DeltaX: %d\tDeltaY: %d\n", deltaX, deltaY);
  // Check if the move only in one direction, just in the X or Y only.
  if ((deltaX <= 1) && (deltaY <= 1)) {
    validity = 1;
  }
  // Check if the destination square is occupied by own piece
  if (islower(board[destRow][destCol])) {
    validity = 0;
     char message[] = "Invalid Move. You have a piece there. ";
     popup(message);
  }
  if (isupper(board[destRow][destCol])) {
    validity = 1;
    printf("Capturing Enemy");
    capturingEnemyW(board, orgRow, orgCol, destRow, destCol);
  }
  if(deltaX == 2){
    printf("Castling");
    validity = castlingW(board, orgRow, orgCol,destRow, destCol, kingWmove, rookWmove);
  }

  //Moves to prevent the king from suicide 
   check += PawnAtkB(board, destRow, destCol);
   check += KnightAtkB(board, destRow, destCol);
   check += RookAtkB(board,destRow, destCol);
   check += BishopAtkB(board, destRow, destCol);
   check += QueenAtkB(board, destRow, destCol);
   check += KingAtkB(board, destRow, destCol);
   //validity = kingAtkB(board, orgRow, orgCol, destRow, destCol);

  if (validity == 1 && check == 6) { // once it passes all checks, move the king
    char piece = board[orgRow][orgCol];
    board[orgRow][orgCol] = ' ';
    // Updating the piece
    board[destRow][destCol] = piece;
  }
}

void movePieceW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,int destRow, int destCol) {
  int check = 0;
  // Checking which piece is being moved
  switch (board[orgRow][orgCol]) {
  case 'p': // white pawn
    countW += pawnmovementW(board, orgRow, orgCol, destRow, destCol);
    check = checkKingSafetyW(board);
    if ( check != 0){
      char message[] = "King is in check, Moving that piece does not help.";
      popup(message);
      --countW;
      board[orgRow][orgCol] = 'p';
      board[destRow][destCol] = ' ';
    }
    break;
  case 'r': // white rook
    countW = countW + RookMovementW(board, orgRow, orgCol, destRow, destCol);
    rookWmove = 1;
    check = checkKingSafetyW(board);
    if ( check != 0){
      char message[] = "King is in check, Moving that piece does not help.";
      popup(message);
      --countW;
      board[orgRow][orgCol] = 'r';
      board[destRow][destCol] = ' ';
    }
    break;
  case 'n': // white knight
    countW = countW + knightMovementW(board, orgRow, orgCol, destRow, destCol);
    break;
  case 'b': // white bishop
    countW = countW + bishopmovementW(board, orgRow, orgCol, destRow, destCol);
    break;
  case 'q': // white queen
    countW = countW +QueenmovementW(board, orgRow, orgCol, destRow, destCol);
    break;
  case 'k': // white king
    KingmovementW(board, orgRow, orgCol, destRow, destCol);
    kingWmove = 1;
    break;
  default: // for empty squares
    break;
  }
 
  }

