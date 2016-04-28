/*
** game.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:51:58 2016 HOVER Beckett
** Last update Thu Apr 28 15:52:03 2016 HOVER Beckett
*/
#include "client.h"

int init_game(char* address, int port)
{
  if (
    (g_game = malloc(sizeof(t_game))) == NULL
    || (g_game->socket = connect_to_server(address, port)) < 0
    || (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0))
  {
    return (-1);
  }

  g_game->window = SDL_CreateWindow("Bomberman", 0, 0, 650, 700, 0);
  g_game->renderer = SDL_CreateRenderer(g_game->window, -1, 0);
  SDL_SetRenderDrawColor(g_game->renderer, 112, 200, 160, 255);
  g_game->running = 1;
  g_game->timer = SDL_GetTicks();
  g_game->player_event.x = 0;
  g_game->player_event.y = 0;
  g_game->player_event.direction = 2;
  g_game->player_event.bomb = 0;

  init_actions();
  if (init_textures() < 0)
    return (-1);

  return (0);
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

