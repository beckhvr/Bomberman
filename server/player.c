/*
** player.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:17:09 2016 HOVER Beckett
** Last update Sun Apr 17 23:17:15 2016 HOVER Beckett
*/
#include "server.h"

void add_player(int index, int address)
{
  t_player* player;

  player = game->players[index];
  player->address = address;
  set_player_coordinates(player, index);
  player->hp = 3;
  player->bombs = 1;
  player->range = 60;
  player->cooldown = 0;
  player->damage_cooldown = 0;

  if ((player->events = malloc(sizeof(t_event))) == NULL)
  {
    free(player);
    game->players[index] = NULL;
    close(address);
    return;
  }
  player->events->x = 0;
  player->events->y = 0;
  player->events->direction = 2;
  player->events->bomb = 0;
}

void handle_new_player(int address)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i] == NULL)
    {
      if ((game->players[i] = malloc(sizeof(t_player))) != NULL)
        add_player(i, address);
      else
        close(address);
      break;
    }
  }
}

void free_player(t_player* player)
{
  close(player->address);
  free(player->events);
  free(player);
}

void set_player_coordinates(t_player* player, int i)
{
  player->x = 552;
  player->y = 552;
  player->direction = 2;

  if (i < 2)
  {
    player->y = 52;
  }
  if (((i + 1) % 2) == 1)
  {
    player->x = 52;
  }
}
