#include "server.h"

int init_game()
{
  if (init_map() < 0)
  {
    return (-1);
  }

  init_players();
  game->isRunning = 1;
  return (0);
}

void free_game()
{
  free_map();
  // free lists of bombs and flames ...
  free_players();
}











void run_game_cycle() {
  int i;

  // bombs

  // flames

  // @TODO: clean this up, and check for colisions !!
  for (i = 0; i < 4; i++) {
    if (game->players[i]) {
      game->players[i]->x += game->players[i]->events->x;
      if (game->players[i]->x < 0) {
        game->players[i]->x = 0;
      }
      if (game->players[i]->x > 100) {
        game->players[i]->x = 100;
      }
      game->players[i]->y += game->players[i]->events->y;
      if (game->players[i]->y < 0) {
        game->players[i]->y = 0;
      }
      if (game->players[i]->y > 100) {
        game->players[i]->y = 100;
      }
      game->players[i]->direction = game->players[i]->events->direction;
      if (game->players[i]->events->bomb > 0) {
        printf("PLACING BOMB at : %d - %d\n", game->players[i]->x, game->players[i]->y);
        game->players[i]->events->bomb = 0;
      }
    }
  }



  // blocks

}













void game_loop()
{
  int max;
  int activity;
  struct timeval timeout;
  fd_set socket_list;

  game->socket_list = &socket_list;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  while (game->isRunning)
  {
    max = init_file_listener();
    activity = select(max + 1, game->socket_list, NULL, NULL, &timeout);

    if (activity < 0)
    {
      game->isRunning = 0;
    }
    else if (activity > 0)
    {
      handle_received_event();
    }

    run_game_cycle();
    sendDataToPlayers();

    // we have a little wait period, for the moment it is 1 second
    usleep(160000);
  }
}
