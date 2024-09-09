#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8
int rowEnemy1 = 0;
int ColEnemy1 = 0;

/*
How to define enemy Path?
<enemy path>
look at the kings dest postion, that is planning on moving towards, then scan in a particular direction. i.e. the row, colum, diagonal.
placing the origin or tail of the vector from the dest postion, and then the tip of the vector at those spots checked before being valid. then implement that same idea for the diagonal,coulmn and rows as while loops until it hits a lowercase/uppercase scenario
*/

///////////////White Pieces/////////////////////

int PawnAtkW(char board[BOARD_SIZE][BOARD_SIZE], int destRow, int destCol){

int validity = 1;
int checkRow = destRow + 1;
int checkCol = destCol;
//checks for the black king in the first diagonal slots if there is a white pawn
if(board[checkRow][checkCol+1] == 'p' && (checkCol +1 < 8)) {
  validity = 0;rowEnemy1=checkRow;ColEnemy1=checkCol+1;
}
  if(board[checkRow][checkCol-1] == 'p' && (checkCol -1 > 0)){
    validity =0;rowEnemy1=checkRow;ColEnemy1=checkCol-1;
}

return validity;
}

int KnightAtkW(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){
 
    int validity = 1;
      int checkRow = destRow;
      int checkCol = destCol;

  //Checks for Knights that would be on the top or bottom of the king  
    if(board[checkRow + 2][checkCol+1] == 'n') {
      validity = 0;rowEnemy1 = checkRow + 2;ColEnemy1 = checkCol + 1;
    }
    if(board[checkRow+2][checkCol-1] == 'n'){
      validity = 0;rowEnemy1 = checkRow + 2;ColEnemy1 = checkCol - 1;
    }
    if( board[checkRow-2][checkCol+1] == 'n' ){
    validity = 0;
      rowEnemy1 = checkRow-2;ColEnemy1=checkCol +1;
    }
   if(board[checkRow-2][checkCol-1] == 'n'){
     validity = 0;
     rowEnemy1 = checkRow-2;ColEnemy1 = checkCol-1;
   }

    //Checks for Knights that would be on the left or right of the king  
    if(board[checkRow + 1][checkCol+2] == 'n'){
      validity = 0;rowEnemy1 = checkRow + 1;ColEnemy1 = checkCol+2;
    }
    if(board[checkRow+1][checkCol-2] == 'n' ){
      validity = 0;rowEnemy1 = checkRow + 1;ColEnemy1 = checkCol-2;
    }
    if(board[checkRow-1][checkCol+2] == 'n'){
      validity = 0;rowEnemy1 = checkRow - 1;ColEnemy1=checkCol+2;
    }
    if(board[checkRow-1][checkCol-2] == 'n'){
      validity = 0;rowEnemy1 = checkRow - 1;ColEnemy1=checkCol-2;
    }

    return validity;
    }

int RookAtkW(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){
  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;
  
//Check the top of the king
  for(int i = checkRow; i > 0 && (validity == 1); i--){
    if(board[i][checkCol] == 'r'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
       //printf("check top \n");
       validity = 0;
       break;
    } if((board[i][checkCol] != ' ') && (board[i][checkCol] != 'K' ) ){ break;}
  }
  //check the bottom of the king
  for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
    if(board[i][checkCol] == 'r'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
      //printf("check bottom \n");
      validity = 0;
      break;
  }if(board[i][checkCol] !=  ' ' && (board[i][checkCol] != 'K' ) ){ break;}
  }
  //Check for the left of the king
  for(int i = checkCol; i > 0 && (validity == 1); i--){
    if(board[checkRow][i] == 'r'){
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      //printf("check left side \n");
       validity = 0;
       break;
    }if(board[checkRow][i] !=  ' '&& (board[checkRow][i] != 'K' ) ){ break;}
  }
  //check the right of the king
  for(int i = checkCol; i < BOARD_SIZE && (validity == 1); i++){
    if(board[checkRow][i] == 'r'){
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      // printf("check right side \n");
      validity = 0;
      break;
  } if(board[checkRow][i] !=  ' ' && (board[checkRow][i] != 'K' ) ){ break;}
  }
  return validity;
 }

int BishopAtkW(char board[BOARD_SIZE][BOARD_SIZE], int destRow, int destCol){
  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;
  int possible = 0;
  //Check the Top Right 
    int j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
      if(j > 7){ break;}
      if(board[i][j] == 'b'){
        rowEnemy1 = i;
        ColEnemy1 = j;
        // printf("check top right \n");
        validity = 0;
         break;
      }
      if(board[i][j] != ' ' && (board[i][j] != 'K')){ break;}
      ++j;
    }
    //check the Top Left
     j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
      if(j < 0){ break;}
      if(board[i][j] == 'b'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       // printf("check top left \n");
        validity = 0;
        break;
       // printf("Possibility: %d", possible);
      } if(board[i][j] != ' ' && (board[i][j] != 'K')){ break;}
      --j;
    }
    //Check for the Bottom right
     j = checkCol;
    for(int i = checkRow; (i < 8) && (validity == 1); i++){
      if(j > 7){ break;}
      if(board[i][j] == 'b'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       // printf("check bottom right \n");
        validity = 0;
         break;
      } if(board[i][j] != ' ' && (board[i][j] != 'K')){ break;}
      
      ++j;
    }
    //check for the bottom left
    j = checkCol - 1;
    for(int i = checkRow + 1; i < BOARD_SIZE && (validity == 1); ++i){
      if(j < 0){ break;}
      if(board[i][j] == 'b'){
        rowEnemy1 = i;
        ColEnemy1 = j;
         //printf("check bottom left \n");
        validity= 0;
        break;
    } if(board[i][j] != ' ' && (board[i][j] != 'K')){ break;}
      --j;
    }

   return validity;
   }

int QueenAtkW(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){

  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;
  
  //Horizontal and Vertical moves from Rook Imported
  //Check the top of the king
  for(int i = checkRow; i > 0 && (validity == 1); i--){
    if(board[i][checkCol] == 'q'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
      // printf("check top \n");
       validity = 0;
       break;
    }if(board[i][checkCol] != ' ' && (board[i][checkCol] != 'K') ){ break;}
  }
  //check the bottom of the king
  for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
    if(board[i][checkCol] == 'q'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
      //printf("check bottom \n");
      validity = 0;
      break;
  }if(board[i][checkCol] != ' ' && (board[i][checkCol] != 'K')){ break;}
  }
  //Check for the left of the king
  for(int i = checkCol; i > 0 && (validity == 1); i--){
    if(board[checkRow][i] == 'q'){ 
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      //printf("check left side \n");
       validity = 0;
       break;
    }if(board[checkRow][i] != ' ' && (board[checkRow][i] != 'K')){ break;}
  }
  //check the right of the king
  for(int i = checkCol; i < BOARD_SIZE && (validity == 1); i++){
    if(board[checkRow][i] == 'q'){
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      // printf("check right side \n");
      validity = 0;
      break;
  }if(board[checkRow][i] != ' ' && (board[checkRow][i] != 'K')){ break;}
  }

//Diagonal Moves from Biship imported

  //Check the Top Right 
    int j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
       if(j > 7){ break;}
      if(board[i][j] == 'q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
         //printf("check top right \n");
        validity = 0;
         break;
      }if(board[i][j] != ' ' && (board[i][j] != 'K')){ break;}
      ++j;
    }
    //check the Top Left
     j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
      if(j < 0){ break;}
      if(board[i][j] == 'q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
        //printf("check top left \n");
        validity = 0;
        break;
    }if(board[i][j] != ' ' && (board[i][j] != 'K') ){ break;}
      --j;
    }

    //Check for the Bottom right
     j = checkCol;
    for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
       if(j > 7){ break;}
      if(board[i][j] == 'q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       // printf("check bottom right \n");
        validity = 0;
         break;
      }if(board[i][j] != ' ' && (board[i][j] != 'K') ){ break;}
      ++j;
    }
    //check for the bottom left
    j = checkCol;
    for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
      if(j < 0){ break;}
      if(board[i][j] == 'q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
        // printf("check bottom left \n");
        validity= 0;
        break;
    }if(board[i][j] != ' ' && (board[i][j] != 'K') ){ break;}
      --j;
    }
   return validity;
   }

int KingAtkW(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){

  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;

  //checks for the black king in the first diagonal slots if there is a white pawn
  
  
  
  if( board[checkRow-1][checkCol-1] == 'k') {
    validity=0;rowEnemy1=checkRow-1;ColEnemy1=checkCol-1;
  }
  if(board[checkRow-1][checkCol] == 'k'){
    validity=0;rowEnemy1=checkRow-1;ColEnemy1=checkCol;
  }
  if(board[checkRow-1][checkCol+1] == 'k'){
    validity=0;rowEnemy1=checkRow-1;ColEnemy1=checkCol+1;
  }
  if(board[checkRow][checkCol+1] == 'k'){
    validity=0;rowEnemy1=checkRow;ColEnemy1=checkCol+1;
  }
  if(board[checkRow+1][checkCol+1] == 'k'){
    validity = 0;rowEnemy1 = checkRow+1;ColEnemy1=checkCol+1;
  }
  if(board[checkRow+1][checkCol] == 'k'){
    validity = 0;rowEnemy1 = checkRow+1;ColEnemy1=checkCol;
  }
  if(board[checkRow+1][checkCol-1] == 'k'){
    validity = 0;rowEnemy1=checkRow+1;ColEnemy1=checkCol-1;
  }
  if(board[checkRow][checkCol-1] == 'k'){
  validity = 0; rowEnemy1=checkRow;ColEnemy1=checkCol-1;
  }
  
  return validity;
 }


/////////////Black pieces//////////////////////

int PawnAtkB(char board[BOARD_SIZE][BOARD_SIZE], int destRow, int destCol){

int validity = 1;
int checkRow = destRow -1;
int checkCol = destCol;
//checks for the black king in the first diagonal slots if there is a white pawn
if(board[checkRow][checkCol+1] == 'P'){
  validity=0;rowEnemy1=checkRow;ColEnemy1=checkCol+1;
}
  if(board[checkRow][checkCol-1] == 'P'){
validity = 0;rowEnemy1=checkRow;ColEnemy1=checkCol-1;
}
return validity;
}

int KnightAtkB(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){
  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;
//Checks for Knights that would be on the top or bottom of the king  
  if(board[checkRow + 2][checkCol+1] == 'N') {
    validity = 0;rowEnemy1 = checkRow + 2;ColEnemy1 = checkCol + 1;
  }
  if(board[checkRow+2][checkCol-1] == 'N'){
    validity = 0;rowEnemy1 = checkRow + 2;ColEnemy1 = checkCol - 1;
  }
  if( board[checkRow-2][checkCol+1] == 'N' ){
  validity = 0;
    rowEnemy1 = checkRow-2;ColEnemy1=checkCol +1;
  }
 if(board[checkRow-2][checkCol-1] == 'N'){
   validity = 0;
   rowEnemy1 = checkRow-2;ColEnemy1 = checkCol-1;
 }

  //Checks for Knights that would be on the left or right of the king  
  if(board[checkRow + 1][checkCol+2] == 'N'){
    validity = 0;rowEnemy1 = checkRow + 1;ColEnemy1 = checkCol+2;
  }
  if(board[checkRow+1][checkCol-2] == 'N' ){
    validity = 0;rowEnemy1 = checkRow + 1;ColEnemy1 = checkCol-2;
  }
  if(board[checkRow-1][checkCol+2] == 'N'){
    validity = 0;rowEnemy1 = checkRow - 1;ColEnemy1=checkCol+2;
  }
  if(board[checkRow-1][checkCol-2] == 'N'){
    validity = 0;rowEnemy1 = checkRow - 1;ColEnemy1=checkCol-2;
  }

  return validity;
  }

int RookAtkB(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){
  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;

//Check the top of the king
  for(int i = checkRow; i > 0 && (validity == 1); i--){
    if(board[i][checkCol] == 'R'){
       rowEnemy1 = i;
       ColEnemy1 = checkCol;
       //printf("check top \n");
       validity = 0;
       break;
    } if(board[i][checkCol] != ' ' && (board[i][checkCol] != 'k' )){break;}
  }
  //check the bottom of the king
  for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
    if(board[i][checkCol] == 'R'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
     // printf("check bottom \n");
      validity = 0;
      break;
  }if(board[i][checkCol] !=  ' ' && (board[i][checkCol] != 'k')){ break;}
  }
  //Check for the left of the king
  for(int i = checkCol; i > 0 && (validity == 1); i--){
    if(board[checkRow][i] == 'R'){
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      //printf("check left side \n");
       validity = 0;
       break;
    }if(board[checkRow][i] !=  ' ' && (board[checkRow][i] != 'k')){ break;}
  }
  //check the right of the king
  for(int i = checkCol; i < BOARD_SIZE && (validity == 1); i++){
    if(board[checkRow][i] == 'R'){
       rowEnemy1 = i;
       ColEnemy1 = checkRow;
       //printf("check right side \n");
      validity = 0;
      break;
  } if(board[checkRow][i] !=  ' ' && (board[checkRow][i] != 'k' )){ break;}
  }
  return validity;
 }

int BishopAtkB(char board[BOARD_SIZE][BOARD_SIZE], int destRow, int destCol){

  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;
  int possible;
  //Check the Top Right 
    int j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
      if(j > 7){ break;}
      if(board[i][j] == 'B'){
         rowEnemy1 = i;
         ColEnemy1 = j;
         //printf("check top right \n");
         validity = 0;
         break;
      }
      if(board[i][j] != ' ' && (board[i][j] != 'k')){break;}
      ++j;
    }
    //check the Top Left
     j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
      if(j < 0){break;}
      if(board[i][j] == 'B'){
        rowEnemy1 = i;
        ColEnemy1 = j;
        //printf("check top left \n");
        validity = 0;
        break;
    }else if(board[i][j] != ' ' && (board[i][j] != 'k')){break;}
      --j;
    }
    //Check for the Bottom right
     j = checkCol;
    for(int i = checkRow; (i < 8) && (validity == 1); ++i){
      if(j > 7){ break;}
      if(board[i][j] == 'B'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       // printf("check bottom right \n");
        validity = 0;
         break;
      } if(board[i][j] != ' ' && (board[i][j] != 'k')){ break;}
      ++j;
    }
    //check for the bottom left
    j = checkCol;
    for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
      if(j < 0){break;}
      if(board[i][j] == 'B'){
         rowEnemy1 = i;
         ColEnemy1 = j;
        // printf("check bottom left \n");
        validity = 0;
        break;
    } if(board[i][j] != ' ' && (board[i][j] != 'k')){break;}
      --j;
    }
   return validity;
   }

int QueenAtkB(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){

  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;

  //Horizontal and Vertical moves from Rook Imported
  //Check the top of the king
  for(int i = checkRow; i > 0 && (validity == 1); i--){
    if(board[i][checkCol] == 'Q'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
       //printf("check top \n");
       validity = 0;
       break;
    }if(board[i][checkCol] != ' ' && (board[i][checkCol] != 'k' || board[i][checkCol] != 'K')){break;}
  }
  //check the bottom of the king
  for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
    if(board[i][checkCol] == 'Q'){
      rowEnemy1 = i;
      ColEnemy1 = checkCol;
      //printf("check bottom \n");
      validity = 0;
      break;
  }if(board[i][checkCol] != ' ' && (board[i][checkCol] != 'k' || board[i][checkCol] != 'K')){break;}
  }
  //Check for the left of the king
  for(int i = checkCol; i > 0 && (validity == 1); i--){
    if(board[checkRow][i] == 'Q'){
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      //printf("check left side \n");
       validity = 0;
       break;
    }if(board[checkRow][i] != ' ' && (board[checkRow][i] != 'k' || board[checkRow][i] != 'K')){break;}
  }
  //check the right of the king
  for(int i = checkCol; i < BOARD_SIZE && (validity == 1); i++){
    if(board[checkRow][i] == 'Q'){
      rowEnemy1 = i;
      ColEnemy1 = checkRow;
      // printf("check right side \n");
      validity = 0;
      break;
  }if(board[checkRow][i] != ' ' && (board[checkRow][i] != 'k' || board[checkRow][i] != 'K')){break;}
  }

//Diagonal Moves from Biship imported

  //Check the Top Right 
    int j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
       if(j > 7){ break;}
      if(board[i][j] == 'Q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       //  printf("check top right \n");
        validity = 0;
         break;
      }if(board[i][j] != ' ' && (board[i][j] != 'k')){ break;}
      ++j;
    }
    //check the Top Left
     j = checkCol;
    for(int i = checkRow; i > 0 && (validity == 1); i--){
      if(j < 0){ break;}
      if(board[i][j] == 'Q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       // printf("check top left \n");
        validity = 0;
        break;
    }if(board[i][j] != ' ' && (board[i][j] != 'k')){break;}
      --j;
    }

    //Check for the Bottom right
     j = checkCol;
    for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
       if(j > 7){ break;}
      if(board[i][j] == 'Q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
       // printf("check bottom right \n");
        validity = 0;
         break;
      }if(board[i][j] != ' ' && (board[i][j] != 'k')){break;}
      ++j;
    }
    //check for the bottom left
    j = checkCol;
    for(int i = checkRow; i < BOARD_SIZE && (validity == 1); i++){
      if(j < 0){ break;}
      if(board[i][j] == 'Q'){
        rowEnemy1 = i;
        ColEnemy1 = j;
        // printf("check bottom left \n");
        validity= 0;
        break;
    }if(board[i][j] != ' ' && (board[i][j] != 'k')){break;}
      --j;
    }
   return validity;
   }

int KingAtkB(char board[BOARD_SIZE][BOARD_SIZE],int destRow, int destCol){
  int validity = 1;
  int checkRow = destRow;
  int checkCol = destCol;
  int possible;

  //checks for the black king in the first diagonal slots if there is a white pawn
  if( board[checkRow-1][checkCol-1] == 'K') {
    validity=0;rowEnemy1=checkRow-1;ColEnemy1=checkCol-1;
  }
  if(board[checkRow-1][checkCol] == 'K'){
    validity=0;rowEnemy1=checkRow-1;ColEnemy1=checkCol;
  }
  if(board[checkRow-1][checkCol+1] == 'K'){
    validity=0;rowEnemy1=checkRow-1;ColEnemy1=checkCol+1;
  }
  if(board[checkRow][checkCol+1] == 'K'){
    validity=0;rowEnemy1=checkRow;ColEnemy1=checkCol+1;
  }
  if(board[checkRow+1][checkCol+1] == 'K'){
    validity=0;rowEnemy1=checkRow+1;ColEnemy1=checkCol+1;
  }
  if(board[checkRow+1][checkCol] == 'K'){
    validity=0;rowEnemy1=checkRow+1;ColEnemy1=checkCol;
  }
  if(board[checkRow+1][checkCol-1] == 'K'){
    validity=0;rowEnemy1=checkRow+1;ColEnemy1=checkCol-1;
  }
  if(board[checkRow][checkCol-1] == 'K'){
  validity = 0;rowEnemy1=checkRow;ColEnemy1=checkCol-1;
  }
  
  return validity;
 }

int GetRowEnemy(){return rowEnemy1;}

int GetColEnemy(){return ColEnemy1;}