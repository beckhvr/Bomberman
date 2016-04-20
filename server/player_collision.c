#include "server.h"

int player_element_collision(t_player* player, t_element* element)
{
  t_collider player_collider;
  t_collider element_collider;

  player_collider.x = player->x;
  player_collider.y = player->y;
  player_collider.s = PLAYER_SIZE;

  element_collider.x = element->x;
  element_collider.y = element->y;
  element_collider.s = ELEMENT_SIZE;

  return collision_handler(&player_collider, &element_collider);
}

int compute_player_collisions_with_list(t_player* player, t_element* list)
{
  t_element* element;

  for (element = list; element != NULL; element = element->next)
  {
    if (player_element_collision(player, element) > 0)
    {
      return 1;
    }
  }

  return 0;
}

int player_has_collisions(t_player* player)
{
  int collisions;

  collisions = 0;
  collisions += compute_player_collisions_with_list(player, game->block);
  collisions += compute_player_collisions_with_list(player, game->bomb);

  return collisions;
}
