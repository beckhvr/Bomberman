/*
** list.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Fri Apr 22 07:23:48 2016 HOVER Beckett
** Last update Fri Apr 22 07:23:55 2016 HOVER Beckett
*/
#include "server.h"

void add_element_to_list(t_element** list, t_element* element)
{
  t_element* first_element;

  first_element = *list;
  element->prev = NULL;
  if (first_element != NULL)
  {
    element->next = first_element;
    first_element->prev = element;
  }
  else
    element->next = NULL;
  *list = element;
}

void compute_list(t_element* list)
{
  t_element* runner;

  for (runner = list; runner; runner = runner->next)
  {
    element_movements(runner);
    if (game->element_actions[runner->type])
    {
      game->element_actions[runner->type](runner);
    }
    if (runner->lifespan > 0 && runner->type > 1)
    {
      runner->lifespan -= 1;
    }
  }
}

void set_first_element_of_game_list(t_element* element)
{
  if (element->type < 2)
  {
    game->block = element->next;
    if (game->block)
      game->block->prev = NULL;
  }
  else if (element->type == 2)
  {
    game->bomb = element->next;
    if (game->bomb)
      game->bomb->prev = NULL;
  }
  else
  {
    game->flame = element->next;
    if (game->flame)
      game->flame->prev = NULL;
  }
}

void remove_element(t_element** list, t_element* element)
{
  if (element->prev != NULL)
  {
    element->prev->next = element->next;
    if (element->next != NULL)
    {
      element->next->prev = element->prev;
    }
  }
  else
  {
    if (element->next != NULL)
    {
      element->next->prev = NULL;
    }
    *list = element->next;
  }
  free(element);
}

void clean_up_list(t_element** list)
{
  t_element* runner;
  t_element* next;

  runner = *list;
  while (runner != NULL)
  {
    next = runner->next;
    if (runner->lifespan == 0)
    {
      remove_element(list, runner);
    }
    runner = next;
  }
}
