#include "CapturingEnemyB.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "EnemyPath.h"

#define BOARD_SIZE 8
int kingBmove =0;
int rookBmove =0;
void popupB(const char *message) {
  initscr();
  printw(message);
  refresh();
  getch();
  endwin();
  message = " ";
}

///////PAWN MOVEMENT/////////////
int pawnmovementB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol, int destRow, int destCol){
  int validity = 1;
  printf("%d\n", destRow);
  int DeltaY = (destRow - orgRow); // Delta Y
  int DeltaX = (destCol - orgCol); // Delta X
  printf("DeltaX: %d\nDeltaY: %d\n", DeltaX, DeltaY);
  if (DeltaY < 0) { // Checks the path if pawn is moving backwards
    //printf("Invalid Move. Pawn can not move backwards.\n");
    char message[] = "Invalid Move. Pawn can not move backwards."; popupB(message);
    validity = 0;
  }
  if(DeltaY > 2){
    char message[] = "Invalid Move. Pawn can only move one spot in the y-direction unless it is it's first move, or it is capturing a piece.\n";  popupB(message);
    validity = 0;
  }
  if (DeltaY > 1 && orgRow != 1) { 
   // printf("Invalid Move. Pawn can only move one spot in the y-direction "
           //"unless its first move.";
    char message[] = "Invalid Move. Pawn can only move one spot in the y-direction unless it is it's first move, or it is capturing a piece.\n";  popupB(message);
    validity = 0;
  }
  
  if (validity == 1 && (DeltaY == 1 || DeltaY == -1) &&(DeltaX == 1 || DeltaX == -1)) { 
    // trying to check if the move for diagonal and only by one spot
  char targetPiece = board[destRow][destCol];
    char targetPiece2 = board[destRow - 1][destCol];
  if (islower(targetPiece)) { // scanning if an enemy is present since enemy
                              // is uppercase
    printf("Capturing Enemy %d", board[destRow][destCol]);
    capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
    //board[destRow][destCol] = 80;
  } 
  else if (islower(targetPiece2) && (orgRow == 4)){
    printf("EnPassant\n");
    validity = 1;
    board[destRow-1][destCol] = ' ';
    ++blackScore;
  }else {
    //printf("Invalid Move. Pawn can only move diagonally if an enemy piece is "
           //"present.\n");
    char message[] = "Invalid Move. Pawn can only move diagonally if an enemy piece is present.";  popupB(message);
    validity = 0;
    return 0;
  }
  }
  if (validity == 1 && destRow == 7){
    char message[] = "Pawn can upgrade. Enter the letter of the piece you want to upgrade   to(FirstLetter of piece or N for knight):";  popupB(message);
    char upgrade;
    scanf(" %c", &upgrade);
    upgrade = toupper(upgrade);
    while (upgrade != 'R' && upgrade != 'N' && upgrade != 'B' && upgrade != 'Q'){
      printf("Invalid input. Enter the letter of the piece you want to upgrade to. First     Letter of piece or N for knight"); 
      scanf(" %c", &upgrade);
      upgrade = toupper(upgrade);
    }
    board[destRow][destCol] = upgrade;
    validity = 0;
    board[orgRow][orgCol] = ' ';
  }

  if (validity == 1) {
    char piece = board[orgRow][orgCol];
    board[orgRow][orgCol] = ' ';
    board[destRow][destCol] = piece;
    return 1;
  }
  else {return 0;}
}

//////Knight movement///////////
int knightMovementB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
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
  if (isupper(board[destRow][destCol])) {
    validity = 0;
    return 0;
  } else if (islower(board[destRow][destCol])) {
    validity = 1;
    printf("Capturing Enemy");
   // capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
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

//////ROOK movement///////////
 int RookMovementB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int
 orgCol, int destRow, int destCol, int check){
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
       if(j > destCol){--j;}else if(j<destCol){++j;}
     while (i != destRow || j != destCol){
     if (isupper(board[i][j])) {  // Check if the destination square is occupied by own piece
       validity = 0;
       //printf("Invalid Move. You have a piece there.\n");
        char message[] = "Invalid Move. You have a piece there. ";
        popupB(message);
       return 0;
       break;
     }
     if (islower(board[i][j])) {
       validity = 1;
       printf("Capturing Enemy");
       capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
       break;
     }
      if(i > destRow){--i;}else if(i< destRow){++i;}
      if(j > destCol){--j;}else if(j<destCol){++j;}
     }
       
     }
   if (isupper(board[i][j])) {  // Check if the destination square is occupied by own piece
      validity = 0;
      char message[] = "Invalid Move. You have a piece there. ";
      popupB(message);
     return 0;
    }
    if (islower(board[i][j])) {
      validity = 1;
      printf("Capturing Enemy");
      capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
    }
     if (validity) { // once it passes all checks, move the rook
       char piece = board[orgRow][orgCol];
       board[orgRow][orgCol] = ' ';
       // Updating the piece
       board[destRow][destCol] = piece;
       return 1;
     }
    else{return 0;}
   }


///////Bishop movement/////////
int bishopmovementB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol, int destRow, int destCol) {
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
    char message[] = "Invalid Move. Bishop moves in a diagonal Line."; 
    popupB(message);
    return 0;
  }
  if (checkRow == checkCol) {
    // Checks that there are no pieces in the way
    char piece = board[i][j];
    while (i != destRow){
      piece = board[i][j];
      if (islower(board[i][j])) {
        printf("Capturing Enemy");
        capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
        validity = 1;
        break;
      } else if (isupper(board[i][j])) {
         char message[] = "Invalid Move. You have a piece there. ";
         popupB(message);
        validity = 0;
        return 0;
        break;
      } else {
        validity = 1;
      }
      if (i < destRow) {i = i + 1;if (j < destCol) { j = j + 1;} else {j = j - 1; } }
      else { i = i - 1;if (j < destCol) {j = j + 1;} else {j = j - 1;}}
    } 
    if (i == destRow) {
      piece = board[i][j];
      if (islower(board[i][j])) {
        printf("Capturing Enemy");
        capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
        validity = 1;
      } else if (isupper(board[i][j])) {
         char message[] = "Invalid Move. You have a piece there. ";
         popupB(message);
        validity = 0;
        return 0;
      }
      else {validity = 1;}
    }
    if (validity == 1) {
      char piece = board[orgRow][orgCol];
      board[orgRow][orgCol] = ' ';
      // Updating the piece
      board[destRow][destCol] = piece;
      return 1;
    }
    else {return 0;}

}
}
//////Queen movement///////////
int QueenMovementB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
                    int destRow, int destCol, bool check) {
  int deltaX = abs(destRow - orgRow);
  int deltaY = abs(destCol - orgCol);
  int validity = 0;
  int complete = 0;

  // Bishop
  if (deltaX == deltaY) {
    complete = bishopmovementB(board, orgRow, orgCol, destRow, destCol);
  }
  // Rook Move
  // Check if the move only in one direction, just in the X or Y only.
  else if ((deltaX > 0 && deltaY == 0) || (deltaX == 0 && deltaY > 0)) {
    complete = RookMovementB(board, orgRow, orgCol, destRow, destCol, check);
  }
  else {
     char message[] = "The Queen can only move diagonally, vertically, or horizontally.";
     popupB(message);
  }
  return complete;
}
//////King movement///////////
int KingmovementB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
int destRow, int destCol) {
  int i = orgRow; int j = orgCol;
  int deltaX = abs(destCol - orgCol);
  int deltaY = abs(destRow - orgRow);
  int validity = 0;
  int check = 0;
  // Check if the move only in one direction, just in the X or Y only.
  if ((deltaX <= 1) && (deltaY <= 1)) {
    validity = 1;
  }
  // Check if the destination square is occupied by own piece
  if (isupper(board[destRow][destCol])) {
    validity = 0;
     char message[] = "Invalid Move. You have a piece there. ";
     popupB(message);
  }
  if (islower(board[destRow][destCol])) {
    validity = 1;
    printf("Capturing Enemy\n");
    capturingEnemyB(board, orgRow, orgCol, destRow, destCol);
  }
 // will need to check the safety of the square
  printf("0");
  if(deltaX == 2){
    validity = castlingB(board, orgRow, orgCol,destRow, destCol, kingBmove, rookBmove);
    //ignore error - replit is teasing
  }

//Moves to prevent king from suicide 
   check += PawnAtkW(board, destRow, destCol);
   check += KnightAtkW(board, destRow, destCol);
   check += RookAtkW(board,destRow, destCol);
   check += BishopAtkW(board, destRow, destCol);
   check += QueenAtkW(board, destRow, destCol);
   check += KingAtkW(board,destRow, destCol);
   if(check == 6 && validity == 1){return 1;}
  else {return 0;}
}


void movePieceB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
               int destRow, int destCol, int check) {
  int v = 0;
  switch (board[orgRow][orgCol]) {
    case 'P': // black pawn
      check = 0;
      printf("BLACK PAWN %d %d\n", orgRow, orgCol);
      countB = countB + pawnmovementB(board, orgRow, orgCol, destRow, destCol);
      check = checkKingSafetyB(board);
      printf("check: %d\n", check);
      if ( check != 0){
        char message[] = "King is in check, Moving that piece does not help.";
        popupB(message);
        --countB;
        board[orgRow][orgCol] = 'P';
        board[destRow][destCol] = ' ';
      }
      break;
    case 'R': // black rook
      countB = countB + RookMovementB(board,orgRow,orgCol,destRow,destCol, check);
      check = checkKingSafetyB(board);
      if ( check != 0){
        char message[] = "King is in check, Moving that piece does not help.";
        popupB(message);
        --countB;
        board[orgRow][orgCol] = 'R';
        board[destRow][destCol] = ' ';
      }
      break;
    case 'N': // black knight
      countB = countB + knightMovementB(board, orgRow, orgCol, destRow, destCol);
      check = checkKingSafetyB(board);
      if ( check != 0){
        char message[] = "King is in check, Moving that piece does not help.";
        popupB(message);
        --countB;
        board[orgRow][orgCol] = 'N';
        board[destRow][destCol] = ' ';
      }
      break;
    case 'B': // black bishop
      countB = countB + bishopmovementB(board, orgRow, orgCol, destRow, destCol);
      check = checkKingSafetyB(board);
      if ( check != 0){
        char message[] = "King is in check, Moving that piece does not help.";
        popupB(message);
        --countB;
        board[orgRow][orgCol] = 'B';
        board[destRow][destCol] = ' ';
      }
      break;
    case 'Q': // black queen
      countB = countB + QueenMovementB(board, orgRow, orgCol, destRow, destCol, check);
      check = checkKingSafetyB(board);
      if ( check != 0){
        char message[] = "King is in check, Moving that piece does not help.";
        popupB(message);
        --countB;
        board[orgRow][orgCol] = 'Q';
        board[destRow][destCol] = ' ';
      }
      break;
    case 'K': // black king
      v = KingmovementB(board, orgRow, orgCol, destRow, destCol);
      kingBmove =1;
      check = checkKingSafetyB(board);
      if ( check != 0){
        char message[] = "King is in check, Moving that piece does not help.";
        popupB(message);
        --countB;
        board[orgRow][orgCol] = 'K';
        board[destRow][destCol] = ' ';
      }
      break;
  }


}
