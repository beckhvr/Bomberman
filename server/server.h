/*
** server.h for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:17:29 2016 HOVER Beckett
** Last update Sun Apr 17 23:17:39 2016 HOVER Beckett
*/
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

// // bombs are placed on the closest block in front of the player (we have the x/y of the player, and his direction)
// // from there, we calculate the nest block, and if we can place a bomb, we do. (we can only place a bomb if there are no collisions with players, or blocks)
// typedef struct s_bomb t_bomb;
// struct s_bomb
// {
//   int x;
//   int y;
//   int duration; // this will be the time it has lived. after 3 seconds, it explodes and creates four flames
// };

// // bomb to flame
// // x + 1, y, direction 2
// // x - 1, y, direction 4
// // x, y + 1, direction 3
// // x, y - 1, direction 1
// typedef struct s_flame t_flame;
// struct s_flame
// {
//   int x;
//   int y;
//   int direction; // 1,2,3,4 respectivly up,right,down,left
// };
// // a flame dies once it hits something, but it damages it.

// typedef struct s_block t_block;
// struct s_block
// {
//   int x;
//   int y;
//   int type;
//   t_block* next;
// };




typedef struct s_element t_element;
struct s_element
{
  int x;
  int y;
  int type; // 0 = block, 1 = bomb, 2 = flame
  int lifespan; // ticks it is allowed to be alive. -1 for immortal
  int dx; // velocity per frame x
  int dy; // velocity per frame y
  t_element* prev;
  t_element* next;
};

typedef struct s_collider t_collider;
struct s_collider {
  int x;
  int y;
  int s;
};








typedef struct s_player t_player;
struct s_player
{
  int address; // socket address
  int x;
  int y;
  int direction; // which way is the player faced
  t_event* events;
  int hp; // health points ... once he arrives at 0, he becomes a gost (not allowed to place bombs and can't get hurt)
  int cooldown; // is the player allowed to place bomb
  int damage_cooldown; // is the player allowed to place bomb
};

typedef struct s_game t_game;
struct s_game
{
  int connection_socket;
  fd_set* socket_list;
  int max_socket_address;
  int isRunning;
  t_player* players[4];
  t_element* block; // chained list of blocks
  t_element* bomb; // chained list of bombs
  t_element* flame; // chained list of flames
  void (*element_actions[4])(t_element*); // array of pointers on functions
};

/*----(Prototypes)-----------------------------------------------------------*/
int create_connection_socket(int);
int init_file_listener();
void handle_received_event();
void sendDataToPlayers();
void game_loop();
int init_map();
void free_map();
void init_players();
void free_players();
int get_player_count();
void accept_new_connection();
void add_player(int);
void free_player(t_player*);
void apply_player_event(t_player*, t_event*);
int init_game();
void free_game();
void format_player_info(t_container*);
int collision_handler(t_collider*, t_collider*);
int check_top_left_collision(t_collider*, t_collider*);
int check_top_right_collision(t_collider*, t_collider*);
int check_bottom_left_collision(t_collider*, t_collider*);
int check_bottom_right_collision(t_collider*, t_collider*);
void run_game_cleanup();
void init_element_actions();
void clean_up_list(t_element*);
void compute_list(t_element*);
int place_bomb(int, int, int);
void explode_bomb(t_element*);
int player_element_collision(t_player*, t_element*);
t_element* get_player_collisions_with_list(t_player*, t_element*);
int player_has_collisions(t_player*);
int element_element_collision(t_element*, t_element*);
t_element* get_element_collisions_with_list(t_element*, t_element*);
void run_players_actions();
void run_player_actions(t_player*);


/*----(Globals)--------------------------------------------------------------*/
t_game* game;




