#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8
//This file is for additional functions that help the game run smoothly 

// This function locates the Black King and returns it's row
int findKingBRow(char board[BOARD_SIZE][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j =0; j< 8; ++j){
          if(board[i][j] == 'K'){
            return i;
          }    
    }
  }
}

// This function locates the White King and returns it's row
int findKingWRow(char board[BOARD_SIZE][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j =0; j< 8; ++j){
          if(board[i][j] == 'k'){
            return i;
          }    
    }
  }
}

// This function locates the Black King and returns it's column
int findKingBCol(char board[BOARD_SIZE][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j =0; j< 8; ++j){
          if(board[i][j] == 'K'){
            return j;
          }    
    }
  }
}

// This function locates the White King and returns it's column
int findKingWCol(char board[BOARD_SIZE][BOARD_SIZE]){
  for(int i = 0; i < BOARD_SIZE; i++){
    for(int j =0; j< 8; ++j){
          if(board[i][j] == 'k'){
            return j;
          }    
    }
  }
}

//This Function checks if the black King is in any danger and returns a value to signify what piece is putting the king into danger
int checkKingSafetyB(char board[BOARD_SIZE][BOARD_SIZE]){
  int iK = findKingBRow(board);
  int jK = findKingBCol(board);
 // printf("King is at %d %d\n", iK, jK);
  int checkK = 0;
  int countcheck = 0;
  int check = 0;
  while (countcheck != 5){
  checkK += PawnAtkW(board, iK, jK);++countcheck;
  if (checkK == 0)  {check = 1;break;}
  checkK += KnightAtkW(board, iK, jK);++countcheck;
  if (checkK == 1)  {check = 2;break;}
  checkK += RookAtkW(board, iK, jK);++countcheck;
  if (checkK == 2)  {check = 3;break;}
  checkK += BishopAtkW(board,iK, jK);++countcheck;
  if (checkK == 3)  {check = 4;break;}
  checkK += QueenAtkW(board,iK, jK);++countcheck;
  if (checkK == 4){check = 5;break;}
  }
  return check;
}

//This Function checks if the white King is in any danger and returns a value to signify what piece is putting the king into danger
int checkKingSafetyW(char board[BOARD_SIZE][BOARD_SIZE]){
  int iK = findKingWRow(board);
  int jK = findKingWCol(board);
 // printf("King is at %d %d\n", iK, jK);
  int checkK = 0;
  int countcheck = 0;
  int check = 0;
  while (countcheck != 5){
  checkK += PawnAtkB(board, iK, jK);++countcheck;
  if (checkK == 0)  {check = 1;break;}
  checkK += KnightAtkB(board, iK, jK);++countcheck;
  if (checkK == 1)  {check = 2;break;}
  checkK += RookAtkB(board, iK, jK);++countcheck;
  if (checkK == 2)  {check = 3;break;}
  checkK += BishopAtkB(board,iK, jK);++countcheck;
  if (checkK == 3)  {check = 4;break;}
  checkK += QueenAtkB(board,iK, jK);++countcheck;
  if (checkK == 4){check = 5;break;}
  }
  return check;
}

//This function checks if the White King can castle with the rook
int castlingW(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
 int destRow, int destCol, int kingMove, int rookMove){
  int validity = 1;
  if ((orgRow == 7 && orgCol == 4)&& (kingMove == 0 && rookMove == 0)){
   //check that squares between king and rook are empty
    if(destCol > orgCol){
    for(int i = 5; i <7;++i){
      if(board[7][i] != ' '){
        printf("Pieces are in the way\n");
        validity = 0;
      }
       // Check for security of each square
    }
    }
    if(destCol < orgCol){
    for(int i = 3; i > 0;--i){
      if(board[7][i] != ' '){
        printf("Pieces are in the way\n");
        validity = 0;
      }
      // Check for security of each square
    }
    }
    if (validity == 1){ //The king will move to the input square
      board[7][4] = ' '; 
      if(destCol > 4){ //If the king moves to the right, the rook will move to the left
        board[7][7] = ' ';
        board[7][5] = 'r';
        board[7][6] = 'k';
      }
      else{ //If the king moves to the left the rook will move to the right
        board[7][0] = ' ';
        board[7][3] = 'r';
        board[7][2] = 'k';
      }
      validity = 0;
    }
 }
  else{
    printf("No\n");
    validity = 0;
  }
  return validity;
}


//This function checks if the Black King can castle with the rook
int castlingB(char board[BOARD_SIZE][BOARD_SIZE], int orgRow, int orgCol,
 int destRow, int destCol, int kingMove, int rookMove){
  int validity = 1;
  if ((orgRow == 0 && orgCol == 4)&& (kingMove == 0 && rookMove == 0)){
   //check that squares between king and rook are empty
    if(destCol > orgCol){
    for(int i = 5; i <7;++i){
      if(board[0][i] != ' '){
        printf("Pieces are in the way\n");
        validity = 0;
      }
       // Check for security of each square
    }
    }
    if(destCol <orgRow){
    for(int i = 3; i > 0;--i){
      if(board[0][i] != ' '){
        printf("Pieces are in the way\n");
        validity = 0;
      }
      // Check for security of each square
    }
    }
    if (validity == 1){ //The King moves to the destination Column
      board[0][4] = ' '; 
      board[0][destCol] = 'K';
      if(destCol > 4){ //If the king moves to the right, the rook will move to the left
        board[0][7] = ' ';
        board[0][5] = 'R';
      }
      else{ //If the king moves to the left the rook will move to the right
        board[0][0] = ' ';
        board[0][3] = 'R';
      }
      validity = 0;
    }
 }
  else{
    printf("No\n"); 
    validity = 0;
  }
  return validity;
}