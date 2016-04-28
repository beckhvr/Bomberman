/*
** flame.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Fri Apr 22 07:18:57 2016 HOVER Beckett
** Last update Fri Apr 22 07:19:02 2016 HOVER Beckett
*/
#include "server.h"

void set_flame_movement(t_element* flame, int direction)
{
  flame->dx = 0;
  flame->dy = 0;

  if (direction == 0)
  {
    flame->dy = -1;
  }
  else if (direction == 1)
  {
    flame->dx = 1;
  }
  else if (direction == 2)
  {
    flame->dy = 1;
  }
  else
  {
    flame->dx = -1;
  }
}

void create_flame(int x, int y, int direction, int range)
{
  t_element* flame;

  if ((flame = malloc(sizeof(t_element))) != NULL)
  {
    flame->x = x;
    flame->y = y;
    flame->type = 3;
    set_flame_movement(flame, direction);
    flame->lifespan = range;
    add_element_to_list(&game->flame, flame);
  }
}

void flame_action(t_element* flame)
{
  t_element* block;
  int i;

  if ((block = get_element_collisions_with_list(flame, game->block)) != NULL)
  {
    if (block->type != 0)
    {
      block->lifespan = 0;
    }
    flame->lifespan = 0;
  }

  for (i = 0; i < 4; i++)
  {
    if (game->players[i]
      && player_element_collision(game->players[i], flame) > 0
      && game->players[i]->hp > 0
      && game->players[i]->damage_cooldown == 0)
    {
      game->players[i]->damage_cooldown = 40;
      game->players[i]->hp -= 1;
    }
  }
}
