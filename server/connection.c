/*
** connection.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:14:23 2016 HOVER Beckett
** Last update Sun Apr 17 23:14:35 2016 HOVER Beckett
*/
#include "server.h"

// creating a socket to handle entering connexions.
int create_connection_socket(int port)
{
  int connection_socket;
  struct sockaddr_in sock;
  char yes;

  if ((connection_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    return (-1);
  memset(&sock, 0, sizeof sock);
  sock.sin_family = AF_INET;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = INADDR_ANY;
  yes = '1';
  setsockopt(connection_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
  if ((bind(connection_socket, (struct sockaddr*)&sock, sizeof(sock))) != 0)
  {
    close(connection_socket);
    return (-1);
  }
  if ((listen(connection_socket, 4)) != 0)
  {
    close(connection_socket);
    return (-1);
  }

  return connection_socket;
}

// returns max file listener
int init_file_listener()
{
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
      if (game->players[i]->address > max)
      {
        max = game->players[i]->address;
      }
    }
  }

  return max;
}

void accept_new_connection()
{
  struct sockaddr_in socket_in;
  int len = sizeof(socket_in);
  int new_socket;

  if ((new_socket = accept(
    game->connection_socket, (struct sockaddr *)&socket_in, (socklen_t*)&len))
     < 0)
  {
    return;
  }

  if (get_player_count() < 4)
    add_player(new_socket);
  else
    close(new_socket);
}
