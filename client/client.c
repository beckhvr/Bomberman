/*
** client.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:51:08 2016 HOVER Beckett
** Last update Thu Apr 28 15:51:13 2016 HOVER Beckett
*/
#include "client.h"

int main(int argc, char** argv)
{
  char address[20];

  if (argc < 2)
    strcpy(address, "127.0.0.1");
  else
    strcpy(address, argv[1]);

  if (init_game(address, 3334) < 0)
  {
    return (-1);
  }

  signal(SIGINT, end_game);
  run_game();
  free_textures();
  close(g_game->socket);
  free(g_game);
  return 0;
}

