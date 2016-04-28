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
