#include "server.h"

void display_connection(char* message, int address)
{
  struct sockaddr_in socket_in;
  int addrlen = sizeof(socket_in);

  getpeername(address , (struct sockaddr*)&socket_in , (socklen_t*)&addrlen);
  printf("%s: ip %s , port %d \n", message, inet_ntoa(socket_in.sin_addr) , ntohs(socket_in.sin_port));
}

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
        display_connection("Disconnected", player->address);
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

void handle_received_event() {
  if (FD_ISSET(game->connection_socket, game->socket_list))
  {
    accept_new_player();
  }
  else
  {
    handle_player_event();
  }
}
