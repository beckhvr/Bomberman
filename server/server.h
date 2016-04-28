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

typedef struct s_element t_element;
struct s_element
{
  int x;
  int y;
  int type;
  int lifespan;
  int dx;
  int dy;
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
  int address;
  int x;
  int y;
  int direction;
  t_event* events;
  int hp;
  int bombs;
  int range;
  int cooldown;
  int damage_cooldown;
};

typedef struct s_game t_game;
struct s_game
{
  int connection_socket;
  fd_set* socket_list;
  int max_socket_address;
  int isRunning;
  t_player* players[4];
  t_element* block;
  t_element* bomb;
  t_element* flame;
  t_element* bonus;
  void (*element_actions[9])(t_element*);
};

/*----(Prototypes)-----------------------------------------------------------*/
void init_element_actions();
void element_movements(t_element*);
void run_players_actions();
void set_bomb_coordinates(t_element*, int, int, int);
int bomb_has_collisions(t_element*);
int place_bomb(int, int, int, int);
void bomb_action(t_element*);
void explode_bomb(t_element*);
int collision_handler(t_collider*, t_collider*);
int check_top_left_collision(t_collider*, t_collider*);
int check_top_right_collision(t_collider*, t_collider*);
int check_bottom_left_collision(t_collider*, t_collider*);
int check_bottom_right_collision(t_collider*, t_collider*);
int create_connection_socket(int);
int init_file_listener();
void accept_new_connection();
int element_element_collision(t_element*, t_element*);
t_element* get_element_collisions_with_list(t_element*, t_element*);
t_player* get_element_collisions_with_players(t_element*);
void handle_player_event();
void handle_received_event();
void set_flame_movement(t_element*, int);
void create_flame(int, int, int, int);
void flame_action(t_element*);
int init_game();
void free_game();
void run_game_cycle();
void run_game_cleanup();
void game_loop();
void add_element_to_list(t_element**, t_element*);
void compute_list(t_element*);
void set_first_element_of_game_list(t_element*);
void remove_element(t_element**, t_element*);
void clean_up_list(t_element**);
int create_block(int, int, int);
int init_map();
void free_elements(t_element*);
void free_map();
void set_nth_bit(char*, int, int);
int position_collides_with_list(int, t_element*);
void set_block_on_position(char*, int);
void set_map_block_meta(char*, int);
void send_data_to_players();
int get_left_range(int, int);
void init_players();
int get_player_count();
void handle_new_player(int);
void format_player_info(t_container*);
void free_player(t_player*);
void apply_player_event(t_player*, t_event*);
void run_player_actions(t_player*);
void free_players();
int player_element_collision(t_player*, t_element*);
t_element* get_player_collisions_with_list(t_player*, t_element*);
int player_has_collisions(t_player*);
void bonus_range(t_element*);
void bonus_bombs(t_element*);
void bonus_lives(t_element*);
int bonus_has_collisions(t_element*);
void bonus_range(t_element*);
void bonus_bombs(t_element*);
void bonus_lives(t_element*);
int get_list_size(t_element*);
void add_bonus_to_map();
void set_bonus_meta(char*, int);
void move_player(t_player*);
void handle_bomb_action(t_player*);
void add_player(int, int);
void set_player_coordinates(t_player*, int);
void place_unbreakable_blocks();
void place_unbreakable_blocks();
void place_breakable_blocks();

/*----(Globals)--------------------------------------------------------------*/
t_game* game;
