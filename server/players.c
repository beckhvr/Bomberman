/*
** players.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 14:45:57 2016 HOVER Beckett
** Last update Thu Apr 28 14:46:03 2016 HOVER Beckett
*/
#include "server.h"

void init_players()
{
  int i;

  for (i = 0; i < 4; i++)
  {
    game->players[i] = NULL;
  }
}

void free_players()
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      free_player(game->players[i]);
    }
  }
}
