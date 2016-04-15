#include "server.h"



int main(int argc, char const *argv[])
{
  t_game tmp_game;

  game = &tmp_game;


  // don't end program if we write to a closed socket !
  signal(SIGPIPE, SIG_IGN);


  if ((game->connection_socket = create_connection_socket(3334)) < 0) {
    printf("unable to setup listener socket\n");
    return (-1);
  }

  // init map
  if (init_map() < 0) {
    close(game->connection_socket);
    printf("unable to init map\n");
    return (-1);
  }

  // init players
  init_players();

  // init game
  game->isRunning = 1;
  game_loop();

  free_map();
  // free lists of bombs and flames ...
  free_players();
  close(game->connection_socket);
  return 0;
}
