/*
** game.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:15:22 2016 HOVER Beckett
** Last update Sun Apr 17 23:16:35 2016 HOVER Beckett
*/
#include "server.h"

int init_game()
{
  if (init_map() < 0)
  {
    return (-1);
  }

  init_players();
  init_element_actions();
  game->isRunning = 1;
  return (0);
}

void free_game()
{
  free_map();
  free_players();
}

void run_game_cycle()
{
  compute_list(game->block);
  compute_list(game->bomb);
  compute_list(game->flame);
  compute_list(game->bonus);

  run_players_actions();
  run_game_cleanup();
}

void run_game_cleanup()
{
  clean_up_list(&game->block);
  clean_up_list(&game->bomb);
  clean_up_list(&game->flame);
  clean_up_list(&game->bonus);
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
      game->isRunning = 0;
    else if (activity > 0)
      handle_received_event();

    run_game_cycle();
    send_data_to_players();

    // we have a little wait period, for the moment it is 1 second
    usleep(16000);
  }
}
