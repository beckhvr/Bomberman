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

typedef struct s_game t_game;
struct s_game {
  int socket;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event event;
  Uint32 timer;
  int running;
  SDL_Texture* textures[54];
  t_event player_event;
  int (*action_list[5])(int);
};

t_game* g_game;

int get_nth_bit(char* c, int bit)
{
  return (*c >> bit) & 1;
}

int connect_to_server(char* address, int port)
{
  int connexion_socket;
  struct sockaddr_in dest;

  if ((connexion_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return (-1);
  }

  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);

  if (inet_aton(address, &dest.sin_addr.s_addr) == 0)
  {
    return (-1);
  }

  if (connect(connexion_socket, (struct sockaddr*)&dest, sizeof(dest)) != 0)
  {
    return (-1);
  }

  return connexion_socket;
}

int init_textures()
{
  int i;

  for (i = 0; i < 14; i++)
  {
    g_game->textures[i] = NULL;
  }

  g_game->textures[0] = IMG_LoadTexture(g_game->renderer, "../img/elements.png");
  g_game->textures[10] = IMG_LoadTexture(g_game->renderer, "../img/player1.png");
  g_game->textures[11] = IMG_LoadTexture(g_game->renderer, "../img/player2.png");
  g_game->textures[12] = IMG_LoadTexture(g_game->renderer, "../img/player3.png");
  g_game->textures[13] = IMG_LoadTexture(g_game->renderer, "../img/player4.png");

  return (0);
}

void free_textures() {
  int i;

  for (i = 0; i < 14; i++)
  {
    if (g_game->textures[i] != NULL)
    {
      SDL_DestroyTexture(g_game->textures[i]);
    }
  }
}

int place_bomb(int value)
{
  int prev;

  prev = g_game->player_event.bomb;
  g_game->player_event.bomb = value;

  if (prev != value)
  {
    return (1);
  }

  return (0);
}

int move_left(int value)
{
  int prev;

  prev = g_game->player_event.x;
  if (value == 0 && g_game->player_event.x == -1)
  {
    g_game->player_event.x = 0;
  }
  else if (value == 1)
  {
    g_game->player_event.x = -1;
  }

  if (prev != g_game->player_event.x)
  {
    if (value == 1)
    {
      g_game->player_event.direction = 3;
    }
    return (1);
  }

  return (0);
}

int move_right(int value)
{
  int prev;

  prev = g_game->player_event.x;
  if (value == 0 && g_game->player_event.x == 1)
  {
    g_game->player_event.x = 0;
  }
  else if (value == 1)
  {
    g_game->player_event.x = 1;
  }

  if (prev != g_game->player_event.x)
  {
    if (value == 1)
    {
      g_game->player_event.direction = 1;
    }
    return (1);
  }

  return (0);
}

int move_up(int value)
{
  int prev;

  prev = g_game->player_event.y;
  if (value == 0 && g_game->player_event.y == -1)
  {
    g_game->player_event.y = 0;
  }
  else if (value == 1)
  {
    g_game->player_event.y = -1;
  }

  if (prev != g_game->player_event.y)
  {
    if (value == 1)
    {
      g_game->player_event.direction = 0;
    }
    return (1);
  }

  return (0);
}

int move_down(int value)
{
  int prev;

  prev = g_game->player_event.y;
  if (value == 0 && g_game->player_event.y == 1)
  {
    g_game->player_event.y = 0;
  }
  else if (value == 1)
  {
    g_game->player_event.y = 1;
  }

  if (prev != g_game->player_event.y)
  {
    if (value == 1)
    {
      g_game->player_event.direction = 2;
    }
    return (1);
  }

  return (0);
}

void init_actions()
{
  int i;

  for (i = 0; i < 5; i++)
  {
    g_game->action_list[i] = NULL;
  }

  g_game->action_list[0]  = &move_right;
  g_game->action_list[1] = &move_left;
  g_game->action_list[2] = &move_down;
  g_game->action_list[3] = &move_up;
  g_game->action_list[4]  = &place_bomb;
}


int init_game(char* address, int port)
{
  if ((g_game = malloc(sizeof(t_game))) == NULL)
  {
    return (-1);
  }

  if ((g_game->socket = connect_to_server(address, port)) < 0)
  {
    return (-1);
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
  {
    return (-1);
  }

  g_game->window = SDL_CreateWindow("Bomberman", 0, 0, 650, 650, 0);
  g_game->renderer = SDL_CreateRenderer(g_game->window, -1, 0);
  g_game->running = 1;
  g_game->timer = SDL_GetTicks();
  g_game->player_event.x = 0;
  g_game->player_event.y = 0;
  g_game->player_event.direction = 2;
  g_game->player_event.bomb = 0;

  init_actions();
  if (init_textures() < 0)
  {
    return (-1);
  }

  return (0);
}






int translate_key(int key)
{
  if (key == SDLK_DOWN)
  {
    return 2;
  }
  else if (key == SDLK_UP)
  {
    return 3;
  }
  else if (key == SDLK_LEFT)
  {
    return 1;
  }
  else if (key == SDLK_RIGHT)
  {
    return 0;
  }
  else if (key == 32)
  {
    return 4;
  }

  return 5;
}

int toggle_player_action(int key, int value)
{
  key = translate_key(key);
  // always return old value
  if (g_game->action_list[key] && g_game->action_list[key](value) == 1)
  {
    return (1);
  }

  return (0);
}

void handle_player_actions()
{
  int notify;

  notify = 0;
  while (SDL_PollEvent(&g_game->event))
  {
    if (g_game->event.type == SDL_QUIT)
    {
      g_game->running = 0;
      return;
    }
    else if (g_game->event.type == SDL_KEYDOWN)
    {
      notify += toggle_player_action(g_game->event.key.keysym.sym, 1);
    }
    else if (g_game->event.type == SDL_KEYUP)
    {
      notify += toggle_player_action(g_game->event.key.keysym.sym, 0);
    }
  }

  if (notify)
  {
    send(g_game->socket, &g_game->player_event, sizeof(t_event), 0);
  }
}

void crop_texture(SDL_Rect* crop, int type, int offset)
{
  int i;

  i = ((SDL_GetTicks() - g_game->timer) / 100) % 4;
  crop->x = 50 * type;
  crop->y = offset * 50;
  crop->w = 50;
  crop->h = 50;

  if (type > 2)
  {
    crop->y = 50 * (i);
  }
  if (type > 9)
  {
    crop->x = 50 * offset;
  }
}

SDL_Texture* get_texture(int type)
{
  if (type < 5)
  {
    return g_game->textures[0];
  }

  return g_game->textures[type];
}

void render_tile(int position, int type, int direction)
{
  SDL_Rect rec;
  SDL_Rect crop;

  rec.x = (position % 13) * ELEMENT_SIZE;
  rec.y = (position / 13) * ELEMENT_SIZE;
  rec.w = ELEMENT_SIZE;
  rec.h = ELEMENT_SIZE;

  crop_texture(&crop, type, direction);
  SDL_RenderCopy(g_game->renderer, get_texture(type), &crop, &rec);
}

void render_player(int type, int x, int y, int direction)
{
  SDL_Rect rec;
  SDL_Rect crop;

  rec.x = x - 5;
  rec.y = y - 5;
  rec.w = PLAYER_SIZE;
  rec.h = PLAYER_SIZE;

  crop_texture(&crop, type, direction);
  SDL_RenderCopy(g_game->renderer, get_texture(type), &crop, &rec);
}





void render_block(char*c, int position)
{
  int type;

  type = 0;

  type += get_nth_bit(c, 1);
  type += get_nth_bit(c, 2);

  render_tile(position, type, 0);
}

void render_map(char* map)
{
  int i;

  for (i = 0; i < 169; i++)
  {
    render_block(&map[i], i);
    if (get_nth_bit(&map[i], 3) == 1)
    {
      // TODO: for the moment set to 0
      render_tile(i, 3, 50 * 0);
    }
    if (get_nth_bit(&map[i], 0) == 1)
    {
      // TODO: for the moment set to 0
      render_tile(i, 4, 50 * 0);
    }
  }
}


void render_players(t_player_info players[4])
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (players[i].playing == 1 && players[i].hp > 0)
    {
      render_player(i + 10, players[i].x, players[i].y, players[i].direction);
    }
  }
}



void run_game()
{
  t_container container;

  while (g_game->running) {
    bzero(&container, sizeof(t_container));
    if (recv(g_game->socket, &container, sizeof(container), 0) == 0)
    {
      printf("server disconnected\n");
      break;
    }

    SDL_RenderClear(g_game->renderer);
    handle_player_actions();
    render_map(container.map);
    render_players(container.players);
    SDL_RenderPresent(g_game->renderer);
  }
}

void end_game()
{
  g_game->running = 0;
}

int main(int argc, char** argv)
{
  char address[20];

  if (argc < 2)
  {
    strcpy(address, "127.0.0.1");
  }
  else
  {
    strcpy(address, argv[1]);
  }

  if (init_game(address, 3334) < 0)
  {
    return (-1);
  }

  signal(SIGINT, end_game);
  run_game();
  free_textures();
  close(g_game->socket);
  free(g_game);
  return 0;
}

