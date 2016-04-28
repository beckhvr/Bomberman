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
  // Bit 0 : Indique si la case est en flammes (1) ou non (0)
  set_nth_bit(block, 0, position_collides_with_list(position, game->flame));

  // Bits [1..2] : Indique le type de terrain ( 00 : Terrain vide, 10 : Brique indestructible, 11 : Brique destructible).
  set_block_on_position(block, position);

  // Bit 3 : Présence d'une bombe (0 : Pas de bombe, 1 : Bombe)
  set_nth_bit(block, 3, position_collides_with_list(position, game->bomb));

  // 0000 -> nothing
  // 1010 -> lives
  // 1100 -> bombs -
  // 1101 -> bombs +
  // 1110 -> range -
  // 1111 -> range +
  set_bonus_meta(block, position);
}

void send_data_to_players()
{
  t_container container;
  int i;

  // prepare data to be sent :
  format_player_info(&container);

  // clear the map string container
  bzero(&container.map, sizeof(container.map));

  // prepare map data
  for (i = 0; i < 169; i++)
  {
    // each char is one block of the map
    container.map[i] = '0';
    set_map_block_meta(&container.map[i], i);
  }

  // send it !
  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      send(game->players[i]->address, &container, sizeof(container), 0);
    }
  }
}
