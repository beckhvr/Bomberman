#include "server.h"

void init_players()
{
  int i;

  for (i = 0; i < 4; i++)
  {
    game->players[i] = NULL;
  }
}

int get_player_count()
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


void add_player(int address)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i] == NULL)
    {
      game->players[i] = malloc(sizeof(t_player));

      // all of this extracted to a separat function to set details ...
      game->players[i]->address = address;
      game->players[i]->hp = 3;
      if (i < 3) {
        game->players[i]->x = 0;
      } else {
        game->players[i]->x = 100;
      }
      if ((i % 2) == 1) {
        game->players[i]->y = 0;
      } else {
        game->players[i]->y = 100;
      }
      game->players[i]->direction = 3;
      // t_player_actions actions;
      // int cooldown;


      break;
    }
  }
}

void free_players()
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
