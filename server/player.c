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

      if ((game->players[i] = malloc(sizeof(t_player))) != NULL) {

        //TODO: all of this extracted to a separat function to set details ...
        game->players[i]->address = address;
        game->players[i]->hp = 3;
        if (i < 3) {
          game->players[i]->x = 2;
        } else {
          game->players[i]->x = 200;
        }
        if (((i + 1) % 2) == 1) {
          game->players[i]->y = 2;
        } else {
          game->players[i]->y = 200;
        }
        game->players[i]->direction = 3;

        // TODO: check this malloc also
        game->players[i]->events = malloc(sizeof(t_event));
        game->players[i]->events->x = 0;
        game->players[i]->events->y = 0;
        game->players[i]->events->direction = 3;
        game->players[i]->events->bomb = 0;
      } else {
        close(address);
      }

      break;
    }
  }
}

void formatPlayerInfo(t_container* container)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    container->players[i].playing = 0;
    if (game->players[i])
    {
      container->players[i].playing = 1;
      container->players[i].x = game->players[i]->x;
      container->players[i].y = game->players[i]->y;
      container->players[i].direction = game->players[i]->direction;
      container->players[i].hp = game->players[i]->hp;
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
