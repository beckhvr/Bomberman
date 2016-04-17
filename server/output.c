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

void sendDataToPlayers()
{
  t_container container;
  int i;

  // prepare data to be sent :
  formatPlayerInfo(&container);

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
