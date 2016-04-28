/*
** connect.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:51:41 2016 HOVER Beckett
** Last update Thu Apr 28 15:51:45 2016 HOVER Beckett
*/
#include "client.h"

int get_nth_bit(char* c, int bit)
{
  return (*c >> bit) & 1;
}

int connect_to_server(char* address, int port)
{
  int connexion_socket;
  struct sockaddr_in dest;

  if ((connexion_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    return (-1);
  }

  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);

  if (inet_aton(address, &dest.sin_addr.s_addr) == 0)
  {
    return (-1);
  }

  if (connect(connexion_socket, (struct sockaddr*)&dest, sizeof(dest)) != 0)
  {
    return (-1);
  }

  return connexion_socket;
}
