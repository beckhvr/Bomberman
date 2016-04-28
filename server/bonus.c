#include "server.h"

int bonus_has_collisions(t_element* bonus)
{
  int collision;
  int i;

  collision = 0;
  if (get_element_collisions_with_list(bonus, game->block) != NULL
    || get_element_collisions_with_list(bonus, game->bomb) != NULL
    || get_element_collisions_with_list(bonus, game->bonus) != NULL)
  {
    collision = 1;
  }

  for (i = 0; i < 4; i++)
  {
    if (game->players[i]
        && get_player_collisions_with_list(game->players[i], bonus) != NULL)
    {
      collision += 1;
    }
  }

  return collision;
}
