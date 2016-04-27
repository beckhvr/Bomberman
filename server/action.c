/*
** action.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Fri Apr 22 07:23:31 2016 HOVER Beckett
** Last update Fri Apr 22 07:23:38 2016 HOVER Beckett
*/
#include "server.h"

void bonus_range(t_element* bonus)
{
  t_player* player;

  if ((player = get_element_collisions_with_players(bonus)) != NULL)
  {
    if (bonus->type == 4 && player->range < 90)
    {
      player->range += 30;
    }
    else if (bonus->type == 5 && player->range > 30)
    {
      player->range -= 30;
    }
    bonus->lifespan = 0;
  }
}

void bonus_bombs(t_element* bonus)
{
  t_player* player;

  if ((player = get_element_collisions_with_players(bonus)) != NULL)
  {
    if (bonus->type == 6 && player->bombs < 3)
    {
      player->bombs += 1;
    }
    else if (bonus->type == 7 && player->bombs > 1)
    {
      player->range -= 1;
    }
    bonus->lifespan = 0;
  }
}

void bonus_lives(t_element* bonus)
{
  t_player* player;

  if ((player = get_element_collisions_with_players(bonus)) != NULL)
  {
    if (player->hp < 3)
    {
      player->hp += 1;
    }

    bonus->lifespan = 0;
  }
}

void init_element_actions()
{
  int i;

  for (i = 0; i < 5; i++)
  {
    game->element_actions[i] = NULL;
  }

  game->element_actions[2] = &bomb_action;
  game->element_actions[3] = &flame_action;

  game->element_actions[4] = &bonus_range;
  game->element_actions[5] = &bonus_range;
  game->element_actions[6] = &bonus_bombs;
  game->element_actions[7] = &bonus_bombs;
  game->element_actions[8] = &bonus_lives;

}

void element_movements(t_element* element)
{
  if (element->lifespan % 15 == 0 && element->type == 3)
  {
    element->x += element->dx * ELEMENT_SIZE;
    element->y += element->dy * ELEMENT_SIZE;
  }
}

void run_players_actions()
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      run_player_actions(game->players[i]);
    }
  }
}
