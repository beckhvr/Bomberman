/*
** bomb.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Fri Apr 22 07:20:30 2016 HOVER Beckett
** Last update Fri Apr 22 07:20:50 2016 HOVER Beckett
*/
#include "server.h"

void set_bomb_coordinates(t_element* bomb, int x, int y, int direction)
{
  bomb->x = get_left_range(x, ELEMENT_SIZE);
  bomb->y = get_left_range(y, ELEMENT_SIZE);

  if (direction == 0)
  {
    bomb->y -= ELEMENT_SIZE;
  }
  else if (direction == 1)
  {
    bomb->x += ELEMENT_SIZE;
  }
  else if (direction == 2)
  {
    bomb->y += ELEMENT_SIZE;
  }
  else
  {
    bomb->x -= ELEMENT_SIZE;
  }
}

int bomb_has_collisions(t_element* bomb)
{
  int collision;
  int i;

  collision = 0;
  if (get_element_collisions_with_list(bomb, game->block) != NULL
    || get_element_collisions_with_list(bomb, game->bomb) != NULL)
  {
    collision = 1;
  }

  for (i = 0; i < 4; i++)
  {
    if (game->players[i]
        && get_player_collisions_with_list(game->players[i], bomb) != NULL)
    {
      collision += 1;
    }
  }

  return collision;
}

int place_bomb(int x, int y, int direction, int range)
{
  t_element* bomb;

  if ((bomb = malloc(sizeof(t_element))) != NULL)
  {
    set_bomb_coordinates(bomb, x, y, direction);
    bomb->type = 2;
    bomb->lifespan = 60;
    bomb->dx = range;
    bomb->dy = 0;
    bomb->next = NULL;

    if (bomb_has_collisions(bomb) == 0)
    {
      add_element_to_list(&game->bomb, bomb);
      return (1);
    }
    else
    {
      free(bomb);
    }
  }
  return (0);
}

void bomb_action(t_element* bomb)
{
  if (bomb->lifespan == 1)
  {
    explode_bomb(bomb);
  }
}

void explode_bomb(t_element* bomb)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    create_flame(bomb->x, bomb->y, i, bomb->dx);
  }
}
