/*
** block.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:19:12 2016 HOVER Beckett
** Last update Thu Apr 28 15:19:17 2016 HOVER Beckett
*/
#include "server.h"

int create_block(int type, int x, int y)
{
  t_element* block;

  if ((block = malloc(sizeof(t_element))) == NULL)
  {
    return (-1);
  }

  block->type = type;
  block->x = x;
  block->y = y;
  block->lifespan = -1;
  block->next = game->block;
  block->prev = NULL;
  if (game->block)
  {
    game->block->prev = block;
  }
  game->block = block;
  return (0);
}

void place_unbreakable_blocks()
{
  int y;
  int x;

  for (y = 0; y < 13; y++)
  {
    for (x = 0; x < 13; x++)
    {
      if (y != 0 && y != 12 && x != 0 && x != 12 && y % 2 == 1)
      {
        continue;
      }
      create_block(0, x * 50, y * 50);
      if (y != 0 && y != 12)
        x += 1;
    }
  }
}

void place_breakable_blocks()
{
  int y;
  int x;

  for (y = 1; y < 12; y++)
  {
    for (x = 1; x < 12; x++)
    {
      if (((y == 1 || y == 11) && (x < 3 || x > 9))
        || ((y == 2 || y == 10) && (x == 1 || x == 10))
        || (y % 2 == 0 && x % 2 == 0))
      {
        continue;
      }
      create_block(1, x * 50, y * 50);
    }
  }
}
