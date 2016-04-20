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




void set_nth_bit(char* c, int bit, int value)
{
  *c |= value << bit;
}

// this should be in client actually
int get_nth_bit(char* c, int bit)
{
  return (*c >> bit) & 1;
}



int position_collides_with_list(int position, t_element* list)
{
  t_element element;

  element.x = (position % 12) * ELEMENT_SIZE;
  element.y = (position / 12) * ELEMENT_SIZE;

  if (compute_element_collisions_with_list(&element, list) > 0)
  {
    return (1);
  }

  return 0;
}

void set_map_block_meta(char* block, int position)
{
  // Bit 0 : Indique si la case est en flammes (1) ou non (0)
  set_nth_bit(block, 0, position_collides_with_list(position, game->flame));

  // Bits [1..2] : Indique le type de terrain ( 00 : Terrain vide, 10 : Brique indestructible, 11 : Brique destructible).
  // for the moment, only look if block is present !
  set_nth_bit(block, 1, position_collides_with_list(position, game->block));


  // Bit 3 : Présence d'une bombe (0 : Pas de bombe, 1 : Bombe)
  set_nth_bit(block, 3, position_collides_with_list(position, game->bomb));
}


void sendDataToPlayers()
{
  t_container container;
  int i;

  // prepare data to be sent :
  format_player_info(&container);

  // clear the map string container
  bzero(&container.map, sizeof(container.map));

  for (i = 0; i < 144; i++)
  {
    // each char is one block of the map
    container.map[i] = '0';
    set_map_block_meta(&container.map[i], i);
  }


  // 600 * 600
  // 12 * 12

  // 10 to walk about on

  // length of char* is 144 (really not too bad);








  // prepare map details :
  // ...

  // send it !
  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      send(game->players[i]->address, &container, sizeof(container), 0);
    }
  }
}
