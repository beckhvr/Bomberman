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
int createBlock(int type, int x, int y) {
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



int init_map() {
  game->block = NULL;
  game->bomb = NULL;
  game->flame = NULL;



  // placing sourounding blocks (unbreakable)
  // top
  createBlock(0, 0, 0);
  createBlock(0, 50, 0);
  createBlock(0, 100, 0);
  createBlock(0, 150, 0);
  createBlock(0, 200, 0);
  createBlock(0, 250, 0);
  createBlock(0, 300, 0);
  createBlock(0, 350, 0);
  createBlock(0, 400, 0);
  createBlock(0, 450, 0);
  createBlock(0, 500, 0);
  createBlock(0, 550, 0);
  createBlock(0, 600, 0);

  // bottom
  createBlock(0, 0, 600);
  createBlock(0, 50, 600);
  createBlock(0, 100, 600);
  createBlock(0, 150, 600);
  createBlock(0, 200, 600);
  createBlock(0, 250, 600);
  createBlock(0, 300, 600);
  createBlock(0, 350, 600);
  createBlock(0, 400, 600);
  createBlock(0, 450, 600);
  createBlock(0, 500, 600);
  createBlock(0, 550, 600);
  createBlock(0, 600, 600);

  // left
  createBlock(0, 0, 50);
  createBlock(0, 0, 100);
  createBlock(0, 0, 150);
  createBlock(0, 0, 200);
  createBlock(0, 0, 250);
  createBlock(0, 0, 300);
  createBlock(0, 0, 350);
  createBlock(0, 0, 400);
  createBlock(0, 0, 450);
  createBlock(0, 0, 500);
  createBlock(0, 0, 550);

  // right
  createBlock(0, 600, 50);
  createBlock(0, 600, 100);
  createBlock(0, 600, 150);
  createBlock(0, 600, 200);
  createBlock(0, 600, 250);
  createBlock(0, 600, 300);
  createBlock(0, 600, 350);
  createBlock(0, 600, 400);
  createBlock(0, 600, 450);
  createBlock(0, 600, 500);
  createBlock(0, 600, 550);


  // one on two ...
  createBlock(0, 100, 100);
  createBlock(0, 100, 200);
  createBlock(0, 100, 300);
  createBlock(0, 100, 400);
  createBlock(0, 100, 500);
  createBlock(0, 200, 100);
  createBlock(0, 200, 200);
  createBlock(0, 200, 300);
  createBlock(0, 200, 400);
  createBlock(0, 200, 500);
  createBlock(0, 300, 100);
  createBlock(0, 300, 200);
  createBlock(0, 300, 300);
  createBlock(0, 300, 400);
  createBlock(0, 300, 500);
  createBlock(0, 400, 100);
  createBlock(0, 400, 200);
  createBlock(0, 400, 300);
  createBlock(0, 400, 400);
  createBlock(0, 400, 500);
  createBlock(0, 500, 100);
  createBlock(0, 500, 200);
  createBlock(0, 500, 300);
  createBlock(0, 500, 400);
  createBlock(0, 500, 500);



  // creating some breakable ones
  createBlock(1, 350, 350);
  createBlock(1, 350, 250);
  createBlock(1, 350, 150);










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
