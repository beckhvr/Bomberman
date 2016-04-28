/*
** player_utils.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 14:45:34 2016 HOVER Beckett
** Last update Thu Apr 28 14:45:39 2016 HOVER Beckett
*/
#include "server.h"

int get_player_count()
{
  int count;

  count = 0;
  for (int i = 0; i < 4; i++)
  {
    if (game->players[i])
      count++;
  }

  return count;
}

void apply_player_event(t_player* player, t_event* event)
{
  player->events->x = event->x;
  player->events->y = event->y;
  player->events->direction = event->direction;
  player->events->bomb = event->bomb;
}

void move_player(t_player* player)
{
  int factor;

  factor = 2;
  player->direction = player->events->direction;
  if (player->events->x != 0)
  {
    player->x += player->events->x * factor;
    if (player_has_collisions(player))
      player->x -= player->events->x * factor;
  }
  if (player->events->y != 0)
  {
    player->y += player->events->y * factor;
    if (player_has_collisions(player))
      player->y -= player->events->y * factor;
  }
}

void handle_bomb_action(t_player* player)
{
  int x;
  int y;

  if (player->events->bomb > 0
    && (player->cooldown == 0 || player->bombs > 1) && player->hp > 0)
  {
    x = player->x + (PLAYER_HITBOX_SIZE / 2);
    y = player->y + (PLAYER_HITBOX_SIZE / 2);
    if (place_bomb(x, y, player->direction, player->range) == 1)
    {
      if (player->bombs > 1 && player->cooldown != 0)
      {
        player->bombs -= 1;
        player->cooldown = 0;
      }
      else
        player->cooldown = 100;
      player->events->bomb = 0;
    }
  }
}

void run_player_actions(t_player* player)
{
  move_player(player);

  if (player->cooldown > 0)
    player->cooldown -= 1;
  if (player->damage_cooldown > 0)
    player->damage_cooldown -= 1;

  handle_bomb_action(player);
}
