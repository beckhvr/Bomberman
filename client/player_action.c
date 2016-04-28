/*
** player_action.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:53:23 2016 HOVER Beckett
** Last update Thu Apr 28 15:53:27 2016 HOVER Beckett
*/
#include "client.h"

int place_bomb(int value)
{
  int prev;

  prev = g_game->player_event.bomb;
  g_game->player_event.bomb = value;

  if (prev != value)
    return (1);
  return (0);
}

int move_left(int value)
{
  int prev;

  prev = g_game->player_event.x;
  if (value == 0 && g_game->player_event.x == -1)
    g_game->player_event.x = 0;
  else if (value == 1)
    g_game->player_event.x = -1;

  if (prev != g_game->player_event.x)
  {
    if (value == 1)
      g_game->player_event.direction = 3;
    return (1);
  }
  return (0);
}

int move_right(int value)
{
  int prev;

  prev = g_game->player_event.x;
  if (value == 0 && g_game->player_event.x == 1)
    g_game->player_event.x = 0;
  else if (value == 1)
    g_game->player_event.x = 1;

  if (prev != g_game->player_event.x)
  {
    if (value == 1)
      g_game->player_event.direction = 1;
    return (1);
  }
  return (0);
}

int move_up(int value)
{
  int prev;

  prev = g_game->player_event.y;
  if (value == 0 && g_game->player_event.y == -1)
    g_game->player_event.y = 0;
  else if (value == 1)
    g_game->player_event.y = -1;

  if (prev != g_game->player_event.y)
  {
    if (value == 1)
      g_game->player_event.direction = 0;
    return (1);
  }
  return (0);
}

int move_down(int value)
{
  int prev;

  prev = g_game->player_event.y;
  if (value == 0 && g_game->player_event.y == 1)
    g_game->player_event.y = 0;
  else if (value == 1)
    g_game->player_event.y = 1;

  if (prev != g_game->player_event.y)
  {
    if (value == 1)
      g_game->player_event.direction = 2;
    return (1);
  }
  return (0);
}
