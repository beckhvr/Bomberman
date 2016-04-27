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

        // TODO: all of this extracted to a separat function to set details ...
        game->players[i]->address = address;
        game->players[i]->hp = 3;

        if (i < 2) {
          game->players[i]->y = 52;
        } else {
          game->players[i]->y = 552;
        }
        if (((i + 1) % 2) == 1) {
          game->players[i]->x = 52;
        } else {
          game->players[i]->x = 552;
        }

        game->players[i]->direction = 2;
        game->players[i]->cooldown = 0;
        game->players[i]->damage_cooldown = 0;

        if ((game->players[i]->events = malloc(sizeof(t_event))) == NULL)
        {
          free(game->players[i]);
          game->players[i] = NULL;
          close(address);
          return;
        }
        game->players[i]->events->x = 0;
        game->players[i]->events->y = 0;
        game->players[i]->events->direction = 2;
        game->players[i]->events->bomb = 0;
      } else {
        close(address);
      }

      break;
    }
  }
}

void format_player_info(t_container* container)
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
      container->players[i].bombs = game->players[i]->bombs;
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
  player->events->x = event->x;
  player->events->y = event->y;
  player->events->direction = event->direction;
  player->events->bomb = event->bomb;
}

void run_player_actions(t_player* player)
{
  int factor;

  factor = 2; // speeding up the movement a bit
  player->direction = player->events->direction;

  if (player->events->x != 0)
  {
    player->x += player->events->x * factor;
    if (player_has_collisions(player))
    {
      player->x -= player->events->x * factor;
    }
  }
  if (player->events->y != 0)
  {
    player->y += player->events->y * factor;
    if (player_has_collisions(player))
    {
      player->y -= player->events->y * factor;
    }
  }

  if (player->cooldown > 0)
  {
    player->cooldown -= 1;
  }
  if (player->damage_cooldown > 0)
  {
    player->damage_cooldown -= 1;
  }

  if (player->events->bomb > 0 && player->cooldown == 0 && player->hp > 0)
  {
    if (place_bomb(player->x + (PLAYER_HITBOX_SIZE / 2), player->y + (PLAYER_HITBOX_SIZE / 2), player->direction) == 1)
    {
      player->cooldown = 40;
      player->events->bomb = 0;
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
      free_player(game->players[i]);
    }
  }
}
