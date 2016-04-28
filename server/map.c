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

int init_map()
{
  game->block = NULL;
  game->bomb = NULL;
  game->flame = NULL;
  game->bonus = NULL;

  place_unbreakable_blocks();
  place_breakable_blocks();
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
  free_elements(game->bonus);
}
