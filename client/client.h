/*
** client.h for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:51:27 2016 HOVER Beckett
** Last update Thu Apr 28 15:51:31 2016 HOVER Beckett
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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../shared/shared.h"

#define OFFSET 24;

typedef struct s_game t_game;
struct s_game {
  int socket;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  Uint32 timer;
  int running;
  SDL_Texture* textures[14];
  t_event player_event;
  int (*action_list[6])(int);
};

int init_textures();
void free_textures();
void crop_texture(SDL_Rect*, int, int);
SDL_Texture* get_texture(int);
int init_game(char*, int);
void run_game();
void end_game();
void render_players(t_player_info players[4]);
void render_player(int, int, int, int);
void render_player_hp(int, int);
int place_bomb(int);
int move_left(int);
int move_right(int);
int move_up(int);
int move_down(int);
void init_actions();
int translate_key(int);
int toggle_player_action(int, int);
void handle_player_actions();
void render_tile(int, int, int);
void render_bonus(char*, int);
void render_block(char*, int);
void render_map(char*);
void render_player_bombs(int, int, int);
int get_nth_bit(char*, int);
int connect_to_server(char*, int);

/*----(globals)-------------------------------------- */
t_game* g_game;
