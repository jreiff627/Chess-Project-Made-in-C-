#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define BOARD_SIZE 8

//Including a timer
/*

int seconds = value

while(seconds > 0){
 printf("\rTime: %04d",seconds)
fflush(stdout);
  clock_t stop = clock() + CLOCKS_PER_SEC;
  while(clock90 < stop){}
  seconds--;
}
printf("\r Times's up!\n")
*/
/*int valueTimer = 180;

void Timer(int value){
    int seconds = value;
    int s, m;

  while(seconds > 0){
    s = seconds % 60;
    m = (seconds / 60) % 60;
    
  printf("\b\b\b\b\b\b\b\b\b\b\bTime: %02d:%02d", m, s);
  fflush(stdout);
    clock_t stop = clock() + CLOCKS_PER_SEC;
    while(clock() < stop){}
    seconds--;
  }
  printf("Times's up!");
}
*/
 //Lets Print the board now
 void printBoard(char board[BOARD_SIZE][BOARD_SIZE]){
   printf("     A    B    C    D    E    F    G    H \n");
   printf("  +---------------------------------------+\n");

 //nested forloop for the board
   for(int i = 0; i < BOARD_SIZE; i++){
     //print off the row number
     printf("%d |", 8 -i);

     for(int j=0; j < BOARD_SIZE; j++){
       char piece = board[i][j];
       // determines white or black slots based of if the sum of the row and column is even or odd
       char square = ((i+j) % 2 == 0)? ' ':':';
       
       //Switch statement to convert the char to a Unicode value to print off the special character for the pieces
       if (piece != ' '){
         switch(piece){
           case 'P': printf(" %c♙ |", square); //black pawn
           break;
           case 'p': printf(" %c♟ |", square); //whitepawn
           break;
           case 'R': printf(" %c♖ |", square); //black rook
           break;
           case 'r': printf(" %c♜ |", square); //white rook
           break;
           case 'N': printf(" %c♘ |", square); //black knight
           break;
           case 'n': printf(" %c♞ |", square); //white knight
           break;
           case 'B': printf(" %c♗ |", square); //black bishop
           break;
           case 'b': printf(" %c♝ |", square); //white bishop
           break;
           case 'Q': printf(" %c♕ |", square); //black queen
           break;
           case 'q': printf(" %c♛ |", square); //white queen
           break;
           case 'K': printf(" %c♔ |", square); // black king
           break;
           case 'k': printf(" %c♚ |", square);// white king
           break;
           default: printf(" %c  |" ,square); // for empty squares
         }
       }
      else {
             printf(" %c%c%c|",square,square,square);
           
         }
       if(i == 1 && j == 7){
                 printf("\tBlack Score: %d", scoreCheckB()); //ignore t
             }
            if(i == 6 && j == 7){
                printf("\tWhite Score: %d", scoreCheckW());
            }
          }

       printf(" \n"); //right border
   }
   printf("  +---------------------------------------+\n");
   //end of printing board
 }
