/*
** output.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:16:04 2016 HOVER Beckett
** Last update Sun Apr 17 23:16:57 2016 HOVER Beckett
*/
#include "server.h"

void set_map_block_meta(char* block, int position)
{
  set_nth_bit(block, 0, position_collides_with_list(position, game->flame));
  set_block_on_position(block, position);
  set_nth_bit(block, 3, position_collides_with_list(position, game->bomb));
  /*
    TODO: Remove this comment
    0000 -> nothing
    1010 -> lives
    1100 -> bombs -
    1101 -> bombs +
    1110 -> range -
    1111 -> range +
  */
  set_bonus_meta(block, position);
}

void send_data_to_players()
{
  t_container container;
  int i;

  format_player_info(&container);
  bzero(&container.map, sizeof(container.map));
  for (i = 0; i < 169; i++)
  {
    container.map[i] = '0';
    set_map_block_meta(&container.map[i], i);
  }

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
      send(game->players[i]->address, &container, sizeof(container), 0);
  }
}
