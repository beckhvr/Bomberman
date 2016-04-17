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
  block->next = game->block;
  game->block = block;

  return (0);
}



int init_map() {
  game->block = NULL;
  game->bomb = NULL;
  game->flame = NULL;



  // we will place only a few blocks at the start, to testout collisions. (maybe a players position ?)
  createBlock(0, 0, -50);
  createBlock(0, -50, 0);
  createBlock(0, 50, 0);
  createBlock(0, 0, 50);




  return 0;
}

void free_elements(t_element* list)
{
  t_element* element;
  t_element* to_free;

  element = list;
  while(element != NULL)
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
