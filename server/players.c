#include "server.h"

void init_players(t_game* game)
{
  int i;

  for (i = 0; i < 4; i++) {
    game->players[i] = NULL;
  }
}

void free_players(t_game* game)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      close(game->players[i]->address);
      free(game->players[i]);
    }
  }
}
