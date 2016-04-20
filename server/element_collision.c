#include "server.h"

int element_element_collision(t_element* current, t_element* element)
{
  t_collider c1;
  t_collider c2;

  c1.x = current->x;
  c1.y = current->y;
  c1.s = ELEMENT_SIZE;
  c2.x = element->x;
  c2.y = element->y;
  c2.s = ELEMENT_SIZE;

  return collision_handler(&c1, &c2);
}

t_element* get_element_collisions_with_list(t_element* current, t_element* list)
{
  t_element* element;

  for (element = list; element != NULL; element = element->next)
  {
    if (element_element_collision(current, element) > 0)
    {
      return element;
    }
  }

  return NULL;
}

