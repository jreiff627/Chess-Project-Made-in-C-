# include <stdio.h>


/* Set of Functions for the King to determine if he is in checkmate or not
    My Idea is that we need to check if 3 things are possible
        1. Can the King move out of Harms Way?
        2. Can the offending piece be taken out?
        3. Can one of our pieces move in the way of the offending piece?
        
*/

//Function to check if the King can move
int CanKingMoveW(char board[8][8]){
  char board1[8][8]; //Creating a duplicate allows us to mimic piece movement without changing the actual board
  int colKing = findKingWCol(board);
  int rowKing = findKingWRow(board);
  int validity = 0; // The variable we will use to determine if the king can move or not
  int count = 0;
  int count2 = 0;
  
  for (int i = 0; i < 8; ++i){ 
    // filling the duplicate board with the original board values 
    for (int j = 0; j < 8; ++j){
          board1[i][j] = board[i][j];
  }
  }
  //I will use the duplicate board and try moving the king to open spaces and then check if that movement put it in check or not 
  
  if((rowKing - 1 > 0) && board1[rowKing - 1][colKing] == ' '){
    //Move King 1 space up
    board1[rowKing - 1][colKing] = 'k'; 
    validity = checkKingSafetyW(board1);
    ++count;
  }
  if((rowKing - 1 > 0) && (colKing +1 < 8) && board1[rowKing - 1][colKing] == ' '){
    //Move King forward and right
    board1[rowKing - 1][colKing+1] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing - 1 > 0) && (colKing -1 > 0)&& board1[rowKing - 1][colKing] == ' '){
    //Move King 1 forward and left
    board1[rowKing - 1][colKing-1] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing + 1 < 8) && board1[rowKing + 1][colKing] == ' ') { 
    // Move King 1 space down
    board1[rowKing + 1][colKing] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing + 1 < 8) && (colKing +1 < 8)&& board1[rowKing + 1][colKing + 1] == ' '){
    //Move King backward right diagonal
    board1[rowKing +1 ][colKing + 1] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing + 1 < 8) && (colKing -1 > 0)&& board1[rowKing + 1][colKing - 1] == ' '){
    //Move King backwards left diagonal
    board1[rowKing + 1][colKing - 1] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((colKing -1 > 0)&&board1[rowKing][colKing - 1] == ' '){
    //move King 1 space left
    board1[rowKing][colKing - 1] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((colKing +1 < 8)&& board1[rowKing][colKing + 1] == ' '){
    //move King 1 space right
    board1[rowKing][colKing + 1] = 'k'; 
    validity = checkKingSafetyW(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  //Count will return the number of open spaces the King could move to
  if(count > 0){return 0;}
  else{return (1);}
}

int checkPieceSafetyW(char board[8][8], int i, int j){
  int checkK = 0;
  int countcheck = 0;
  int check = 0;
  while (countcheck != 5){
  checkK += PawnAtkB(board, i, j);++countcheck;
  if (checkK == 0)  {check = 1;break;}
  checkK += KnightAtkB(board,i, j);++countcheck;
  if (checkK == 1)  {check = 2;break;}
  checkK += RookAtkB(board, i, j);++countcheck;
  if (checkK == 2)  {check = 3;break;}
  checkK += BishopAtkB(board,i, j);++countcheck;
  if (checkK == 3)  {check = 4;break;}
  checkK += QueenAtkB(board,i, j);++countcheck;
  if (checkK == 4){check = 5;break;}
  }
  return check;
}

int RookBlockW(char board[8][8], int rowPiece, int colPiece, int rowKing, int colKing){
  int canPieceBlock = 0;
  int j = colPiece;
  if((rowPiece < rowKing) && (colPiece == colKing)){
    printf("Testing 1\n");
    for(int i = rowPiece; i < rowKing; i++){
      canPieceBlock += checkPieceSafetyB(board, i, colPiece);
      if(checkPieceSafetyB(board,i,j) == 1){
        //If it returns one it means the pawn can move diagonally to block, that is not true so I decrement if the pawn can move
        --canPieceBlock;
      }
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
    }
  }
  else if((rowPiece < rowKing) && (colPiece == colKing)){
    printf("Testing 2\n");
    for(int i = rowPiece; i < rowKing; i++){
      canPieceBlock += checkPieceSafetyB(board, i, colPiece);
      if(checkPieceSafetyB(board,i,j) == 1){
        --canPieceBlock;
      }
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
    }
  }
  else if(rowPiece == rowKing && colPiece < colKing){
    printf("Testing 3\n");
    for(int i = colPiece; i < colKing; i++){
      canPieceBlock += checkPieceSafetyB(board, rowPiece, i);
      if(checkPieceSafetyB(board,i,j) == 1){
        --canPieceBlock;
      }
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
    }
  }
  else if(rowPiece == rowKing && colPiece > colKing){
    printf("Testing 4\n");
    for(int i = colPiece; i > colKing; i--){
      canPieceBlock += checkPieceSafetyB(board, rowPiece, i);
      if(checkPieceSafetyB(board,i,j) == 1){
        --canPieceBlock;
      }
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
    }
  }
  //can PieceBlock will be zero if no piece can block the path, any other number indicates a piece can move and block the path
  return canPieceBlock;
  
}

int BishopBlockW(char board[8][8], int rowPiece, int colPiece, int rowKing, int colKing){
  int canPieceBlock = 0;
  int j = colPiece;
  if(rowPiece < rowKing && colPiece < colKing){
  for(int i = rowPiece; i < rowKing; i++){
    printf("1-Row: %d Col: %d Num: %d\n", i, j, canPieceBlock);
    canPieceBlock += checkPieceSafetyB(board, i, j);
    if(checkPieceSafetyB(board,i,j) == 1){
      --canPieceBlock;
    }
    //I am manually checking for a pawn
    if (board[i+1][j] == 'p'){ ++canPieceBlock; }
    ++j;
  }
  }
  else if(rowPiece < rowKing && colPiece > colKing){
    for(int i = rowPiece; i < rowKing; i++){
      printf("2-Row: %d Col: %d Num: %d\n", i, j, canPieceBlock);
      int maybe = checkPieceSafetyB(board, i, j);
      if(maybe == 1){}
      else{canPieceBlock += maybe;}
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
      --j;
    }
  }
  else if(rowPiece > rowKing && colPiece < colKing){
    for(int i = rowPiece; i > rowKing; i--){
      canPieceBlock += checkPieceSafetyB(board, i, j);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
      ++j;
    }
  }
  else if(rowPiece > rowKing && colPiece > colKing){
    for(int i = rowPiece; i > rowKing; i--){
      canPieceBlock += checkPieceSafetyB(board, i, j);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
      //I am manually checking for a pawn
      if (board[i+1][j] == 'p'){ ++canPieceBlock; }
      --j;
    }
  }
  return canPieceBlock;
}


/////////////Black pieces//////////////////////
int CanKingMoveB(char board[8][8]){
  char board1[8][8]; //Creating a duplicate allows us to mimic piece movement without changing the actual board
  int colKing = findKingBCol(board);
  int rowKing = findKingBRow(board);
  int validity = 1; // The variable we will use to determine if the king can move or not
  int count = 0;
  int count2 =0;

  for (int i = 0; i < 8; ++i){ 
    // filling the duplicate board with the original board values 
    for (int j = 0; j < 8; ++j){
          board1[i][j] = board[i][j];
  }
  }
  //I will use the duplicate board and try moving the king to open spaces and then check if that movement put it in check or not 

  if((rowKing - 1 > 0) && board1[rowKing - 1][colKing] == ' '){
    //Move King 1 space up
    board1[rowKing - 1][colKing] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing - 1 > 0) && (colKing +1 < 8) && board1[rowKing - 1][colKing] == ' '){
    //Move King forward and right
    board1[rowKing - 1][colKing+1] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing - 1 > 0) && (colKing -1 > 0)&& board1[rowKing - 1][colKing] == ' '){
    //Move King 1 forward and left
    board1[rowKing - 1][colKing-1] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing + 1 < 8) && board1[rowKing + 1][colKing] == ' ') { 
    // Move King 1 space down
    board1[rowKing + 1][colKing] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing + 1 < 8) && (colKing +1 < 8)&& board1[rowKing + 1][colKing + 1] == ' '){
    //Move King backward right diagonal
    board1[rowKing +1 ][colKing + 1] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((rowKing + 1 < 8) && (colKing -1 > 0)&& board1[rowKing + 1][colKing - 1] == ' '){
    //Move King backwards left diagonal
    board1[rowKing + 1][colKing - 1] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((colKing -1 > 0)&&board1[rowKing][colKing - 1] == ' '){
    //move King 1 space left
    board1[rowKing][colKing - 1] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  if((colKing +1 < 8)&& board1[rowKing][colKing + 1] == ' '){
    //move King 1 space right
    board1[rowKing][colKing + 1] = 'K'; 
    validity = checkKingSafetyB(board1);
    if(validity == 0){++count2;}
    ++count;
  }
  //Count will return the number of open spaces the King could move to
  //If validity is less than count, there is an open space the King could move to
  if(count2 > 0){return 0;}
  else{return (1);}
}

int checkPieceSafetyB(char board[BOARD_SIZE][BOARD_SIZE], int i, int j){

  int checkK = 0;
  int countcheck = 0;
  int check = 0;
  while (countcheck != 5){
  checkK += PawnAtkW(board, i, j);++countcheck;
  if (checkK == 0)  {check = 1;break;}
  checkK += KnightAtkW(board, i, j);++countcheck;
  if (checkK == 1)  {check = 2;break;}
  checkK += RookAtkW(board, i, j);++countcheck;
  if (checkK == 2)  {check = 3;break;}
  checkK += BishopAtkW(board,i, j);++countcheck;
  if (checkK == 3)  {check = 4;break;}
  checkK += QueenAtkW(board,i, j);++countcheck;
  if (checkK == 4) {check = 5;break;}
  }
  return check;
}

int RookBlockB(char board[8][8], int rowPiece, int colPiece, int rowKing, int colKing){
  int canPieceBlock = 0;
  int j = colPiece;
  if(rowPiece < rowKing && colPiece == colKing){
    for(int i = rowPiece; i < rowKing; i++){
      canPieceBlock += checkPieceSafetyW(board, i, colPiece);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
    }
  }
  else if(rowPiece < rowKing && colPiece == colKing){
    for(int i = rowPiece; i < rowKing; i++){
      canPieceBlock += checkPieceSafetyW(board, i, colPiece);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
    }
  }
  else if(rowPiece == rowKing && colPiece < colKing){
    for(int i = colPiece; i < colKing; i++){
      canPieceBlock += checkPieceSafetyW(board, rowPiece, i);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
      //I now manually check the space for a pawn
      if(board[i-1][j] == 'P'){canPieceBlock += 1;}
    }
  }
  else if(rowPiece == rowKing && colPiece > colKing){
    for(int i = colPiece; i > colKing; i--){
      canPieceBlock += checkPieceSafetyW(board, rowPiece, i);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
      //I now manually check the space for a pawn
      if(board[i-1][j] == 'P'){canPieceBlock += 1;}
    }
  }
  //can PieceBlock will be zero if no piece can block the path, any other number indicates a piece can move and block the path
  return canPieceBlock;

}

int BishopBlockB(char board[8][8], int rowPiece, int colPiece, int rowKing, int colKing){
  int canPieceBlock = 0;
  int j = colPiece;
  if(rowPiece < rowKing && colPiece < colKing){
  for(int i = rowPiece; i < rowKing; i++){
    canPieceBlock += checkPieceSafetyW(board, i, j);
    if(checkPieceSafetyW(board,i,j) == 1){
      --canPieceBlock;
    }
    //I now manually check the space for a pawn
    if(board[i-1][j] == 'P'){canPieceBlock += 1;}
    ++j;
  }
  }
  else if(rowPiece < rowKing && colPiece > colKing){
    for(int i = rowPiece; i < rowKing; i++){
      canPieceBlock += checkPieceSafetyW(board, i, j);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
      //I now manually check the space for a pawn
      if(board[i-1][j] == 'P'){canPieceBlock += 1;}
      --j;
    }
  }
  else if(rowPiece > rowKing && colPiece < colKing){
    for(int i = rowPiece; i > rowKing; i--){
      canPieceBlock += checkPieceSafetyW(board, i, j);
      if(checkPieceSafetyW(board,i,j) == 1){
        --canPieceBlock;
      }
      //I now manually check the space for a pawn
      if(board[i-1][j] == 'P'){canPieceBlock += 1;}
      ++j;
    }
  }
  else if(rowPiece > rowKing && colPiece > colKing){
    for(int i = rowPiece; i > rowKing; i--){
      canPieceBlock += checkPieceSafetyW(board, i, j);
      if(checkPieceSafetyW(board,i,j) == 1){ 
        //If it returns one it means the pawn can move diagonally to block, that is not true so I decrement if the pawn can move
        --canPieceBlock;
      }
      //I now manually check the space for a pawn
      if(board[i-1][j] == 'P'){canPieceBlock += 1;}
      --j;
    }
  }
  return canPieceBlock;
}
