#include "server.h"

void init_players(t_game* game)
{
  int i;

  for (i = 0; i < 4; i++) {
    game->players[i] = NULL;
  }
}

int get_player_count(t_game* game)
{
  int count;

  count = 0;
  for (int i = 0; i < 4; i++)
  {
    if(game->players[i])
    {
      count++;
    }
  }

  return count;
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
