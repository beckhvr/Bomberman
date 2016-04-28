/*
** output_utils.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 14:18:10 2016 HOVER Beckett
** Last update Thu Apr 28 14:18:16 2016 HOVER Beckett
*/
#include "server.h"

void set_bonus_meta(char* c, int position)
{
  t_element element;
  t_element* bonus;

  element.x = (position % 13) * ELEMENT_SIZE;
  element.y = (position / 13) * ELEMENT_SIZE;

  set_nth_bit(c, 4, 0);
  set_nth_bit(c, 5, 0);
  set_nth_bit(c, 6, 0);
  set_nth_bit(c, 7, 0);

  bonus = get_element_collisions_with_list(&element, game->bonus);
  if (bonus)
  {
    /* TODO : check that I am using the correct things for life bonus ... */
    set_nth_bit(c, 5, 1);
    if (bonus->type < 8)
    {
      if (bonus->type > 5)
        set_nth_bit(c, 6, 1);
      if (bonus->type % 2 == 1)
        set_nth_bit(c, 7, 1);
    }
  }
}

void set_nth_bit(char* c, int bit, int value)
{
  /*
    TODO: remove this once i'm sure the algorythm is good
    *c |= value << bit;
  */
  *c ^= (-value ^ *c) & (1 << bit);

}

int position_collides_with_list(int position, t_element* list)
{
  t_element element;

  element.x = (position % 13) * ELEMENT_SIZE;
  element.y = (position / 13) * ELEMENT_SIZE;

  if (get_element_collisions_with_list(&element, list) != NULL)
  {
    return (1);
  }

  return 0;
}

void set_block_on_position(char* c, int position)
{
  t_element element;
  t_element* block;

  element.x = (position % 13) * ELEMENT_SIZE;
  element.y = (position / 13) * ELEMENT_SIZE;

  if ((block = get_element_collisions_with_list(&element, game->block)) == NULL)
  {
    set_nth_bit(c, 1, 0);
    set_nth_bit(c, 2, 0);
    return;
  }

  set_nth_bit(c, 1, 1);
  set_nth_bit(c, 2, block->type);
}

void format_player_info(t_container* container)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    container->players[i].playing = 0;
    if (game->players[i])
    {
      container->players[i].playing = 1;
      container->players[i].x = game->players[i]->x;
      container->players[i].y = game->players[i]->y;
      container->players[i].direction = game->players[i]->direction;
      container->players[i].hp = game->players[i]->hp;
      container->players[i].bombs = game->players[i]->bombs;
      container->players[i].cooldown = game->players[i]->cooldown;
    }
  }
}
