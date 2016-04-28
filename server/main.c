/*
** main.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:15:38 2016 HOVER Beckett
** Last update Sun Apr 17 23:16:14 2016 HOVER Beckett
*/
#include "server.h"

int main()
{
  int port;

  port = 3334;
  if ((game = malloc(sizeof(t_game))) == NULL)
  {
    printf("unable to allocate space for game\n");
    return (-1);
  }

  signal(SIGPIPE, SIG_IGN);
  if ((game->connection_socket = create_connection_socket(port)) < 0)
  {
    printf("unable to setup listener socket\n");
    return (-1);
  }

  if (init_game() == 0)
  {
    game_loop();
    free_game();
  }

  close(game->connection_socket);
  return (0);
}
