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

int gameEnd(void)
{
    int i;
    int flag_end = 1;
    
    for (i=0;i<N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_LIVE)
           flag_end = 0;
    }
    return flag_end;
}

void checkDie(void)
{
     int i;
     
     for(i=0; i<N_PLAYER; i++)
     {
         if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
         {
            player_status[i] = PLAYERSTATUS_DIE;
            printf("So sad! %s died at position %i!\n",
                       player_name[i], player_position[i]);
            }
     }
}

int rolldice(void)
{
    int dice= rand() % MAX_DICE+1;
    return dice;
}

//winner select
int maxCoinPlayer(void)
{
    int i;
    int maxCoin = -1;
    int winner = -1;
    
    for (i=0; i<N_PLAYER; i++)
    {
        if (player_status[i] == PLAYERSTATUS_DIE)
           continue;
           
        if (player_coin[i] > maxCoin)
        {
           maxCoin = player_coin[i];
           winner = i;
           }
        else if (player_coin[i] == maxCoin)
             winner = -1;
    }
    return winner;
}

//game
int main(int argc, char *argv[])
{
  int turn;
  int dum;
  int boardCoin;
  
  srand( (unsigned) (time(NULL)) );
  //opening
  printf("____________________________________________\n");
  printf("быбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбы\n");
  printf("в╞               GAME START                в╞\n");
  printf("быбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбыбы\n");
  printf("============================================\n\n\n");
  
  //step 1. initialization (player name setting, variables)
  //1-1. board init
  board_initBoard();
  initPlayer();
  //1-2. player init
  

  //step 2. tunr play (do-while)
  turn = 0;
  
  do {
     int die_result;
     
     if (player_status[turn] != PLAYERSTATUS_LIVE)
     {
        turn = (turn+1) % N_PLAYER;
        if (turn==0)
        {
           int shark_pos = board_stepShark();
           printf("Shark moved to %i\n", shark_pos);
           
           checkDie();
           }
        continue;
        }
        
     // 2-1. status printing
     board_printBoardStatus();
     //player status(░в└┌) 
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
     
     boardCoin = board_getBoardCoin(player_position[turn]);
     player_coin[turn] += board_getBoardCoin(player_position[turn]);
     printf("%s got %i coin\n", player_name[turn], boardCoin);
     
     
     // 2-4. change turn, shark move
     // change turn
     turn= (turn+1)%N_PLAYER;
     // shark move
     if (turn==0)
     {
        int shark_pos = board_stepShark();
        printf("Shark moved to %i\n", shark_pos);
        
        checkDie();
     }
  }
  while(gameEnd() == 0); //game end condition
  
  //step 3. game end (winner printing)
  int winner= maxCoinPlayer();
  
  if (winner < 0)
     printf("Tie! No winner.");
  else
      printf("Winner is %s!", player_name[winner]);
  
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
 
