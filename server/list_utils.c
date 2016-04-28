/*
** list_utils.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 14:12:36 2016 HOVER Beckett
** Last update Thu Apr 28 14:12:40 2016 HOVER Beckett
*/
#include "server.h"

int get_list_size(t_element* list)
{
  int i;
  t_element* element;

  for (element = list, i = 0; element != NULL; element = element->next, i++);
  return i;
}
