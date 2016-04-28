/*
** action.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:50:36 2016 HOVER Beckett
** Last update Thu Apr 28 15:50:47 2016 HOVER Beckett
*/
#include "client.h"

void init_actions()
{
  int i;

  for (i = 0; i < 6; i++)
  {
    g_game->action_list[i] = NULL;
  }

  g_game->action_list[0]  = &move_right;
  g_game->action_list[1] = &move_left;
  g_game->action_list[2] = &move_down;
  g_game->action_list[3] = &move_up;
  g_game->action_list[4]  = &place_bomb;
}

int translate_key(int key)
{
  if (key == SDLK_DOWN)
    return 2;
  else if (key == SDLK_UP)
    return 3;
  else if (key == SDLK_LEFT)
    return 1;
  else if (key == SDLK_RIGHT)
    return 0;
  else if (key == 32)
    return 4;

  return 5;
}

int toggle_player_action(int key, int value)
{
  key = translate_key(key);
  if (g_game->action_list[key] != NULL && g_game->action_list[key](value) == 1)
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
