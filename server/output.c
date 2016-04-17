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
