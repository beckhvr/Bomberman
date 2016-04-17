#include "server.h"

// type can by destructable or undestructable
// blocks have a fixed size of lets say 50px
int createBlock(int type, int x, int y) {
  t_block* block;

  if ((block = malloc(sizeof(block))) == NULL)
  {
    return (-1);
  }

  block->type = type;
  block->x = x;
  block->y = y;
  block->hp = 1;
  block->next = game->block;
  game->block = block;

  return (0);
}



int init_map() {
  game->block = NULL;
  game->bomb = NULL;
  game->flame = NULL;

  // we will place only a few blocks at the start, to testout collisions. (maybe a players position ?)
  createBlock(0, 50, 0);
  createBlock(0, 0, 50);

  return 0;
}

void free_blocks()
{
  t_block* block;
  t_block* to_free;

  block = game->block;

  while(block != NULL)
  {
    to_free = block;
    block = block->next;
    free(to_free);
  }
}

void free_map()
{
  free_blocks();
}
