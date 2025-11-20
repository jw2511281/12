#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DICE           6

int rolldice(void)
{
    int dice= rand() % MAX_DICE+1;
    return dice;
}

int main(int argc, char *argv[])
{
  int cnt;
  int pos;
  
  srand( (unsigned) (time(NULL)) );
  //opening
  printf("____________________________________________\n");
  printf("быбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбы\n");
  printf("в╞               GAME START                в╞\n");
  printf("быбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбы\n");
  printf("============================================\n\n\n");
  
  //step 1. initialization (player name setting, variables)
  board_initBoard();
  
  //step 2. tunr play (do-while)
  cnt = 0;
  pos = 0;
  
  do {
     int die_result;
     int coin_result;
      
     // 2-1. status printing
     board_printBoardStatus();
     
     // 2-2. roll dice
     die_result = rolldice();
     
     // 2-3. move (result)
     pos+= die_result;
     
     printf("pos : %i (dice: %i )\n", pos, die_result);
     
     coin_result = board_getBoardCoin(pos);
     
     printf("coin: %i\n", coin_result);
     
     // 2-4. change turn, shark move
     cnt++;
  }
  while(cnt<5);
  //step 3. game end (winner printing)
  
  
  //ending
  printf("\n\n\n\n\n\n\n\n");
  printf("____________________________________________\n");
  printf("быбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбы\n");
  printf("в╞               GAME END                  в╞\n");
  printf("быбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбы\n");
  printf("============================================\n");
  
  system("PAUSE");	
  return 0;
}
 
