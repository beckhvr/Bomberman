/*
** map.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:15:51 2016 HOVER Beckett
** Last update Sun Apr 17 23:16:20 2016 HOVER Beckett
*/
#include "server.h"

// type can by destructable or undestructable
// blocks have a fixed size of lets say 50px
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

int init_map()
{
  game->block = NULL;
  game->bomb = NULL;
  game->flame = NULL;

  // placing sourounding blocks (unbreakable)
  // top
  create_block(0, 0, 0);
  create_block(0, 50, 0);
  create_block(0, 100, 0);
  create_block(0, 150, 0);
  create_block(0, 200, 0);
  create_block(0, 250, 0);
  create_block(0, 300, 0);
  create_block(0, 350, 0);
  create_block(0, 400, 0);
  create_block(0, 450, 0);
  create_block(0, 500, 0);
  create_block(0, 550, 0);
  create_block(0, 600, 0);

  // bottom
  create_block(0, 0, 600);
  create_block(0, 50, 600);
  create_block(0, 100, 600);
  create_block(0, 150, 600);
  create_block(0, 200, 600);
  create_block(0, 250, 600);
  create_block(0, 300, 600);
  create_block(0, 350, 600);
  create_block(0, 400, 600);
  create_block(0, 450, 600);
  create_block(0, 500, 600);
  create_block(0, 550, 600);
  create_block(0, 600, 600);

  // left
  create_block(0, 0, 50);
  create_block(0, 0, 100);
  create_block(0, 0, 150);
  create_block(0, 0, 200);
  create_block(0, 0, 250);
  create_block(0, 0, 300);
  create_block(0, 0, 350);
  create_block(0, 0, 400);
  create_block(0, 0, 450);
  create_block(0, 0, 500);
  create_block(0, 0, 550);

  // right
  create_block(0, 600, 50);
  create_block(0, 600, 100);
  create_block(0, 600, 150);
  create_block(0, 600, 200);
  create_block(0, 600, 250);
  create_block(0, 600, 300);
  create_block(0, 600, 350);
  create_block(0, 600, 400);
  create_block(0, 600, 450);
  create_block(0, 600, 500);
  create_block(0, 600, 550);

  // one on two ...
  create_block(0, 100, 100);
  create_block(0, 100, 200);
  create_block(0, 100, 300);
  create_block(0, 100, 400);
  create_block(0, 100, 500);
  create_block(0, 200, 100);
  create_block(0, 200, 200);
  create_block(0, 200, 300);
  create_block(0, 200, 400);
  create_block(0, 200, 500);
  create_block(0, 300, 100);
  create_block(0, 300, 200);
  create_block(0, 300, 300);
  create_block(0, 300, 400);
  create_block(0, 300, 500);
  create_block(0, 400, 100);
  create_block(0, 400, 200);
  create_block(0, 400, 300);
  create_block(0, 400, 400);
  create_block(0, 400, 500);
  create_block(0, 500, 100);
  create_block(0, 500, 200);
  create_block(0, 500, 300);
  create_block(0, 500, 400);
  create_block(0, 500, 500);

  create_block(1, 50, 200);
  create_block(1, 50, 300);
  create_block(1, 50, 400);

  create_block(1, 150, 50);
  create_block(1, 150, 100);
  create_block(1, 150, 150);
  create_block(1, 150, 200);
  create_block(1, 150, 250);
  create_block(1, 150, 300);
  create_block(1, 150, 350);
  create_block(1, 150, 400);
  create_block(1, 150, 450);
  create_block(1, 150, 500);
  create_block(1, 150, 550);

  create_block(1, 250, 50);
  create_block(1, 250, 100);
  create_block(1, 250, 150);
  create_block(1, 250, 200);
  create_block(1, 250, 250);
  create_block(1, 250, 300);
  create_block(1, 250, 350);
  create_block(1, 250, 400);
  create_block(1, 250, 450);
  create_block(1, 250, 500);
  create_block(1, 250, 550);

  create_block(1, 350, 50);
  create_block(1, 350, 100);
  create_block(1, 350, 150);
  create_block(1, 350, 200);
  create_block(1, 350, 250);
  create_block(1, 350, 300);
  create_block(1, 350, 350);
  create_block(1, 350, 400);
  create_block(1, 350, 450);
  create_block(1, 350, 500);
  create_block(1, 350, 550);

  create_block(1, 450, 50);
  create_block(1, 450, 100);
  create_block(1, 450, 150);
  create_block(1, 450, 200);
  create_block(1, 450, 250);
  create_block(1, 450, 300);
  create_block(1, 450, 350);
  create_block(1, 450, 400);
  create_block(1, 450, 450);
  create_block(1, 450, 500);
  create_block(1, 450, 550);

  create_block(1, 550, 200);
  create_block(1, 550, 300);
  create_block(1, 550, 400);

  create_block(1, 200, 50);
  create_block(1, 300, 50);
  create_block(1, 400, 50);

  create_block(1, 50, 150);
  create_block(1, 100, 150);
  create_block(1, 200, 150);
  create_block(1, 300, 150);
  create_block(1, 400, 150);
  create_block(1, 500, 150);

  create_block(1, 50, 250);
  create_block(1, 100, 250);
  create_block(1, 200, 250);
  create_block(1, 300, 250);
  create_block(1, 400, 250);
  create_block(1, 500, 250);
  create_block(1, 550, 250);

  create_block(1, 50, 350);
  create_block(1, 100, 350);
  create_block(1, 200, 350);
  create_block(1, 300, 350);
  create_block(1, 400, 350);
  create_block(1, 500, 350);
  create_block(1, 550, 350);

  create_block(1, 50, 450);
  create_block(1, 100, 450);
  create_block(1, 200, 450);
  create_block(1, 300, 450);
  create_block(1, 400, 450);
  create_block(1, 500, 450);
  create_block(1, 550, 450);

  create_block(1, 200, 550);
  create_block(1, 300, 550);
  create_block(1, 400, 550);

  return 0;
}

void free_elements(t_element* list)
{
  t_element* element;
  t_element* to_free;

  element = list;
  while (element != NULL)
  {
    to_free = element;
    element = element->next;
    free(to_free);
  }
}

void free_map()
{
  free_elements(game->block);
  free_elements(game->bomb);
  free_elements(game->flame);
}
