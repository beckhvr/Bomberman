#include "server.h"

// creating a socket to handle entering connexions.
int create_connection_socket(int port) {
  int connection_socket;
  struct sockaddr_in socket_in;
  char yes;

  if ((connection_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    return -1;

  memset(&socket_in, 0, sizeof socket_in);
  socket_in.sin_family = AF_INET;
  socket_in.sin_port = htons(port);
  socket_in.sin_addr.s_addr = INADDR_ANY;
  yes = '1';
  setsockopt(connection_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  if ((bind(connection_socket, (struct sockaddr*)&socket_in, sizeof(socket_in))) != 0)
  {
    close(connection_socket);
    return -1;
  }

  if ((listen(connection_socket, 4)) != 0)
  {
    close(connection_socket);
    return -1;
  }

  return connection_socket;
}

// returns max file listener
int initFileListener(t_game* game) {
  int max;
  int i;

  FD_ZERO(game->socket_list);
  FD_SET(game->connection_socket, game->socket_list);
  max = game->connection_socket;

  for (i = 0 ; i < 4; i++)
  {
    if (game->players[i] != NULL)
    {
      FD_SET(game->players[i]->address, game->socket_list);
      if(game->players[i]->address > max)
      {
        max = game->players[i]->address;
      }
    }
  }

  return max;
}

