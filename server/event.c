/*
** event.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:14:58 2016 HOVER Beckett
** Last update Sun Apr 17 23:15:08 2016 HOVER Beckett
*/
#include "server.h"

void handle_player_event()
{
  t_event event;
  t_player* player;

  for (int i = 0; i < 4; i++) {
    if ((player = game->players[i]) == NULL)
    {
      continue;
    }

    if (FD_ISSET(player->address, game->socket_list))
    {
      if (read(player->address, &event, sizeof(t_event)) == 0)
      {
        free_player(player);
        game->players[i] = NULL;
      }
      else
      {
        apply_player_event(player, &event);
      }
    }
  }
}

void handle_received_event()
{
  if (FD_ISSET(game->connection_socket, game->socket_list))
  {
    accept_new_connection();
  }
  else
  {
    handle_player_event();
  }
}
