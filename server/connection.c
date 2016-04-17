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
  struct sockaddr_in socket_in;
  char yes;

  if ((connection_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    return (-1);

  memset(&socket_in, 0, sizeof socket_in);
  socket_in.sin_family = AF_INET;
  socket_in.sin_port = htons(port);
  socket_in.sin_addr.s_addr = INADDR_ANY;
  yes = '1';
  setsockopt(connection_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  if ((bind(connection_socket, (struct sockaddr*)&socket_in, sizeof(socket_in))) != 0)
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
int init_file_listener() {
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

void accept_new_connection() {
  struct sockaddr_in socket_in;
  int addrlen = sizeof(socket_in);
  int new_socket;

  if ((new_socket = accept(game->connection_socket, (struct sockaddr *)&socket_in, (socklen_t*)&addrlen)) < 0)
  {
    return;
  }

  //inform user of socket number - used in send and receive commands
  printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket, inet_ntoa(socket_in.sin_addr), ntohs(socket_in.sin_port));


  if (get_player_count() < 4)
  {
    add_player(new_socket);
  }
  else
  {
    printf("let's tell them to fuckoff ... \n");
    close(new_socket);
  }
}
