/*
** bonus.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 14:03:48 2016 HOVER Beckett
** Last update Thu Apr 28 14:03:53 2016 HOVER Beckett
*/
#include "server.h"

int bonus_has_collisions(t_element* bonus)
{
  int collision;
  t_player* player;
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
    player = game->players[i];
    if (player && get_player_collisions_with_list(player, bonus) != NULL)
      collision += 1;
  }

  return collision;
}

void bonus_range(t_element* bonus)
{
  t_player* player;

  if ((player = get_element_collisions_with_players(bonus)) != NULL)
  {
    if (bonus->type == 4 && player->range < 90)
      player->range += 30;
    else if (bonus->type == 5 && player->range > 30)
      player->range -= 30;
    bonus->lifespan = 0;
  }
}

void bonus_bombs(t_element* bonus)
{
  t_player* player;

  if ((player = get_element_collisions_with_players(bonus)) != NULL)
  {
    if (bonus->type == 6 && player->bombs < 3)
      player->bombs += 1;
    else if (bonus->type == 7 && player->bombs > 1)
      player->range -= 1;
    bonus->lifespan = 0;
  }
}

void bonus_lives(t_element* bonus)
{
  t_player* player;

  if ((player = get_element_collisions_with_players(bonus)) != NULL)
  {
    if (player->hp < 3)
      player->hp += 1;
    bonus->lifespan = 0;
  }
}

void add_bonus_to_map()
{
  int i;
  t_element* bonus;

  i = rand() % 169;
  if ((bonus = malloc(sizeof(t_element))) != NULL)
  {
    bonus->x = i % 13 * ELEMENT_SIZE;
    bonus->y = i / 13 * ELEMENT_SIZE;

    // TODO : random number between 4 and 8 !!
    bonus->type = 4;

    bonus->lifespan = 200;
    bonus->dx = 0;
    bonus->dy = 0;
    bonus->next = NULL;
    bonus->prev = NULL;

    if (bonus_has_collisions(bonus) != 0)
      add_element_to_list(&game->bonus, bonus);
    else
      free(bonus);
  }
}
