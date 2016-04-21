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
  // remove blocks that need to be
  compute_list(game->block);
  // see if bombs need to explode. remove those that need to be
  compute_list(game->bomb);
  // move the flames. damages things it hits
  compute_list(game->flame);

  // TODO: check if player takes damage -> damage cooldown + hp--
  // this should be done in the flame action ...
  run_players_actions();

  run_game_cleanup();
}

int get_left_range(int point, int increments)
{
  int i;

  i = 0;
  while (point > i * increments)
  {
    i++;
  }

  return i * increments;
}

void set_bomb_coordinates(t_element* bomb, int x, int y, int direction)
{
  bomb->x = get_left_range(x, ELEMENT_SIZE);
  bomb->y = get_left_range(y, ELEMENT_SIZE);

  if (direction == 1)
  {
    bomb->y -= ELEMENT_SIZE;
  }
  else if (direction == 2)
  {
    bomb->x += ELEMENT_SIZE;
  }
  else if (direction == 3)
  {
    bomb->y += ELEMENT_SIZE;
  }
  else
  {
    bomb->x -= ELEMENT_SIZE;
  }
}

int bomb_has_collisions(t_element* bomb)
{
  int collision;
  int i;

  collision = 0;
  if (get_element_collisions_with_list(bomb, game->block) != NULL
    || get_element_collisions_with_list(bomb, game->bomb) != NULL)
  {
    collision = 1;
  }

  for (i = 0; i < 4; i++)
  {
    if (game->players[i]
        && get_player_collisions_with_list(game->players[i], bomb) != NULL)
    {
      collision += 1;
    }
  }

  return collision;
}

void add_element_to_list(t_element** list, t_element* element) {
  t_element* first_element;

  first_element = *list;
  element->prev = NULL;
  if (first_element != NULL)
  {
    element->next = first_element;
    first_element->prev = element;
  }
  else
    element->next = NULL;
  *list = element;
}

int place_bomb(int x, int y, int direction)
{
  t_element* bomb;

  if ((bomb = malloc(sizeof(t_element))) != NULL)
  {
    set_bomb_coordinates(bomb, x, y, direction);
    bomb->type = 2;
    bomb->lifespan = 60;
    bomb->dx = 0;
    bomb->dy = 0;

    if (bomb_has_collisions(bomb) == 0)
    {
      add_element_to_list(&game->bomb, bomb);
      return (1);
    }
    else
    {
      free(bomb);
    }
  }
  return (0);
}


void set_flame_movement(t_element* flame, int direction)
{
  flame->dx = 0;
  flame->dy = 0;

  if (direction == 0)
  {
    flame->dy = -1;
  }
  else if (direction == 1)
  {
    flame->dx = 1;
  }
  else if (direction == 2)
  {
    flame->dy = 1;
  }
  else
  {
    flame->dx = -1;
  }
}

void create_flame(int x, int y, int direction)
{
  t_element* flame;

  if ((flame = malloc(sizeof(t_element))) != NULL)
  {
    flame->x = x;
    flame->y = y;
    flame->type = 3;
    set_flame_movement(flame, direction);
    flame->lifespan = 30;
    add_element_to_list(&game->flame, flame);
  }
}

void bomb_action(t_element* bomb)
{
  if (bomb->lifespan == 1)
  {
    explode_bomb(bomb);
  }
}

void explode_bomb(t_element* bomb)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    create_flame(bomb->x, bomb->y, i);
  }
}








void flame_action(t_element* flame)
{
  t_element* block;
  int i;

  if ((block = get_element_collisions_with_list(flame, game->block)) != NULL)
  {
    if (block->type != 0)
    {
      block->lifespan = 0;
    }
    flame->lifespan = 0;
  }

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      if (player_element_collision(game->players[i], flame) > 0)
      {
        if (game->players[i]->hp > 0 && game->players[i]->damage_cooldown == 0)
        {
          game->players[i]->damage_cooldown = 40;
          game->players[i]->hp -= 1;
        }
      }
    }
  }
}

void init_element_actions()
{
  int i;

  for (i = 0; i < 4; i++)
  {
    game->element_actions[i] = NULL;
  }

  game->element_actions[2] = &bomb_action;
  game->element_actions[3] = &flame_action;
}

void element_movements(t_element* element)
{
  // only move every 5 frames ...
  if (element->lifespan % 15 == 0 && element->type == 3)
  {
    element->x += element->dx * ELEMENT_SIZE;
    element->y += element->dy * ELEMENT_SIZE;
  }
}

void compute_list(t_element* list)
{
  t_element* runner;

  for (runner = list; runner; runner = runner->next)
  {
    // we compute the movement of each element
    element_movements(runner);

    if (game->element_actions[runner->type])
    {
      game->element_actions[runner->type](runner);
    }

    // do not diminish life of blocks (that will be done in the collisions)
    if (runner->lifespan > 0 && runner->type > 1)
    {
      runner->lifespan -= 1;
    }
  }
}

void set_first_element_of_game_list(t_element* element)
{
  if (element->type < 2)
  {
    game->block = element->next;
    if (game->block)
      game->block->prev = NULL;
  }
  else if (element->type == 2)
  {
    game->bomb = element->next;
    if (game->bomb)
      game->bomb->prev = NULL;
  }
  else
  {
    game->flame = element->next;
    if (game->flame)
      game->flame->prev = NULL;
  }
}

void run_game_cleanup()
{
  clean_up_list(&game->block);
  clean_up_list(&game->bomb);
  clean_up_list(&game->flame);
}

void remove_element(t_element** list, t_element* element) {
  if (element->prev != NULL)
  {
    element->prev->next = element->next;
    if (element->next != NULL)
    {
      element->next->prev = element->prev;
    }
  }
  else
  {
    if (element->next != NULL)
    {
      element->next->prev = NULL;
    }
    *list = element->next;
  }
  free(element);
}





void clean_up_list(t_element** list)
{
  t_element* runner;
  t_element* next;

  runner = *list;
  while (runner != NULL)
  {
    next = runner->next;
    if (runner->lifespan == 0)
    {
      remove_element(list, runner);
    }
    runner = next;
  }
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
    usleep(16000);
  }
}
