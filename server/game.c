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
  free_players();
}

int player_element_colision(t_player* player, t_element* element)
{
  t_collider player_collider;
  t_collider element_collider;

  player_collider.x = player->x;
  player_collider.y = player->y;
  player_collider.s = PLAYER_SIZE;

  element_collider.x = element->x;
  element_collider.y = element->y;
  element_collider.s = ELEMENT_SIZE;

  return collision_handler(&player_collider, &element_collider);
}

int compute_player_colisions_with_list(t_player* player, t_element* list)
{
  t_element* element;

  for (element = list; element != NULL; element = element->next)
  {
    if (player_element_colision(player, element) > 0)
    {
      return 1;
    }
  }

  return 0;
}

int player_has_colisions(t_player* player)
{
  int colisions;

  colisions = 0;
  colisions += compute_player_colisions_with_list(player, game->block);
  colisions += compute_player_colisions_with_list(player, game->bomb);

  return colisions;
}



void run_player_actions(t_player* player)
{
  player->direction = player->events->direction;
  player->x += player->events->x;
  if (player_has_colisions(player))
  {
    player->x -= player->events->x;
  }
  player->y += player->events->y;
  if (player_has_colisions(player))
  {
    player->y -= player->events->y;
  }

  //TODO: place bomb
  if (player->events->bomb > 0) {
    printf("PLACING BOMB at : %d - %d\n", player->x, player->y);
    player->events->bomb = 0;
  }


}

void run_players_actions()
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      run_player_actions(game->players[i]);
    }
  }
}




void run_game_cycle() {

  // bombs

  // flames


  // TODO: check if player takes damage -> damage cooldown + hp--
  run_players_actions();




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
