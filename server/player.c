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
    if (game->players[i])
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


      game->players[i]->events = malloc(sizeof(t_event));
      game->players[i]->events->x = 0;
      game->players[i]->events->y = 0;
      game->players[i]->events->direction = 3;
      game->players[i]->events->bomb = 0;

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

void apply_player_event(t_player* player, t_event* event)
{
  player->events->x += event->x;
  player->events->y += event->y;
  player->events->direction = event->direction;
  player->events->bomb = event->bomb;
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
