#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DICE           6
#define N_PLAYER           3
#define MAXLENGTH          30

#define PLAYERSTATUS_LIVE  0
#define PLAYERSTATUS_DIE   1
#define PLAYERSTATUS_END   2

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAXLENGTH];
int player_coin[N_PLAYER];
int player_status[N_PLAYER]; //0=live 1=die 2=end
char player_statusString[3][MAXLENGTH] = {"LIVE", "DIE", "END"};

void printPlayerPosition(int player)
{
     int i;
     for (i=0; i<N_BOARD; i++)
     {
         printf("|");
         if (i== player_position[player])
         {
            printf("%c", player_name[player][0]);
            }
         else
         {
             if(board_getBoardStatus(i) == BOARDSTATUS_OK)
                 printf(" ");
             else
                 printf("X");
             }
     }
     printf("|\n");
}

void printPlayerStatus(void)
{
     int i;
     for(i=0;i<N_PLAYER; i++)
     {
         printf("%s : pos %i, coin %i, status %s\n",
                    player_name[i],
                    player_position[i],
                    player_coin[i],
                    player_statusString[player_status[i]] );
         printPlayerPosition(i);
         }
}

void initPlayer(void)
{
     int i;
     for (i=0;i<N_PLAYER; i++)
     {
         player_position[i] = 0;
         player_coin[i] = 0;
         player_status[i] = PLAYERSTATUS_LIVE;
         printf("Player %i's name: ", i+1);
         scanf("%s", player_name[i]);
         fflush(stdin);
         }
}

int rolldice(void)
{
    int dice= rand() % MAX_DICE+1;
    return dice;
}

int main(int argc, char *argv[])
{
  //임시변수 cnt 
  int cnt;
  int turn;
  int dum;
  
  srand( (unsigned) (time(NULL)) );
  //opening
  printf("____________________________________________\n");
  printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
  printf("▒               GAME START                ▒\n");
  printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
  printf("============================================\n\n\n");
  
  //step 1. initialization (player name setting, variables)
  //1-1. board init
  board_initBoard();
  initPlayer();
  //1-2. player init
  

  //step 2. tunr play (do-while)
  cnt = 0;
  turn = 0;
  
  do {
     int die_result;
      
     // 2-1. status printing
     board_printBoardStatus();
     //player status(각자) 
     printPlayerStatus();
     
     // 2-2. roll dice
     printf("%s turn! ", player_name[turn]);
     printf("Press any key to roll a dice!\n");
     scanf("%d", &dum);
     fflush(stdin);
     die_result = rolldice(); //player turn 
     
     // 2-3. move (result)
     player_position[turn] += die_result;
     if (player_position[turn]  >= N_BOARD-1)
     {
        player_position[turn] = N_BOARD-1;
        player_status[turn] = PLAYERSTATUS_END;
        }
     printf("Dice result : %i, %s moved to %i\n", die_result, player_name[turn], player_position[turn]);
     
     player_coin[turn] = board_getBoardCoin(player_position[turn]);
     printf("%s got %i coin\n", player_name[turn], player_coin[turn]);
     
     
     // 2-4. change turn, shark move
     // change turn
     turn= (turn+1)%N_PLAYER;
     // shark move
     cnt++;
  }
  while(cnt<5); //game end condition
  
  //step 3. game end (winner printing)
  
  
  //ending
  printf("\n\n\n\n\n\n\n\n");
  printf("____________________________________________\n");
  printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
  printf("▒               GAME END                  ▒\n");
  printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n");
  printf("============================================\n");
  
  system("PAUSE");	
  return 0;
}
 
