#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../shared/shared.h"

// bombs are placed on the closest block in front of the player (we have the x/y of the player, and his direction)
// from there, we calculate the nest block, and if we can place a bomb, we do. (we can only place a bomb if there are no colisions with players, or blocks)
typedef struct s_bomb
{
  int x;
  int y;
  int duration; // this will be the time it has lived. after 3 seconds, it explodes and creates four flames
} t_bomb;

// bomb to flame
// x + 1, y, direction 2
// x - 1, y, direction 4
// x, y + 1, direction 3
// x, y - 1, direction 1
typedef struct s_flame
{
  int x;
  int y;
  int direction; // 1,2,3,4 respectivly up,right,down,left
} t_flame;
// a flame dies once it hits something, but it damages it.

typedef struct s_block
{
  int x;
  int y;
  int type;
  int hp;
} t_block;

typedef struct s_player_actions
{
  int x; // -1, 0 or 1
  int y; // -1, 0 or 1
} t_player_actions;

typedef struct s_player
{
  int address; // socket address
  int x;
  int y;
  int direction; // which way is the player faced
  t_player_actions actions;
  int hp; // health points ... once he arrives at 0, he becomes a gost (not allowed to place bombs and can't get hurt)
  int cooldown; // is the player allowed to place bomb
} t_player;

typedef struct s_game
{
  int connection_socket;
  fd_set* socket_list;
  int max_socket_address;
  int isRunning;
  t_player* players[4];
  t_block* blocks; // chained list of blocks
  t_bomb* bombs; // chained list of bombs
  t_flame* flame; // chained list of flames
} t_game;

/*----(Prototypes)-----------------------------------------------------------*/
int create_connection_socket(int);
int initFileListener(t_game*);
void handleReceivedEvent(t_game*);
void sendDataToPlayers(t_game*);
void game_loop(t_game*);
int init_map(t_game*);
void free_map(t_game*);
void init_players(t_game*);
void free_players(t_game*);
int get_player_count(t_game*);
void handleNewPlayer(t_game*);
