/*
** collision.c for Bomberman in /Users/becketthover/Desktop/Bomberman/server
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Sun Apr 17 23:13:56 2016 HOVER Beckett
** Last update Sun Apr 17 23:14:07 2016 HOVER Beckett
*/
#include "server.h"

int collision_handler(t_collider* c1, t_collider* c2)
{
  int collision;

  collision = 0;
  collision += check_top_left_collision(c1, c2);
  collision += check_top_right_collision(c1, c2);
  collision += check_bottom_left_collision(c1, c2);
  collision += check_bottom_right_collision(c1, c2);
  collision += check_top_left_collision(c2, c1);
  collision += check_top_right_collision(c2, c1);
  collision += check_bottom_left_collision(c2, c1);
  collision += check_bottom_right_collision(c2, c1);
  return collision;
}

int check_top_left_collision(t_collider* c1, t_collider* c2)
{
  if (c1->x >= c2->x && c1->x < (c2->x + c2->s))
  {
    if (c1->y >= c2->y && c1->y < (c2->y + c2->s))
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }
  else
  {
    return (0);
  }
}

int check_top_right_collision(t_collider* c1, t_collider* c2)
{
  if ((c1->x + c1->s) > c2->x && (c1->x + c1->s) < (c2->x + c2->s))
  {
    if (c1->y > c2->y && c1->y < (c2->y + c2->s))
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }
  else
  {
    return (0);
  }
}

int check_bottom_left_collision(t_collider* c1, t_collider* c2)
{
  if (c1->x > c2->x && c1->x < (c2->x + c2->s))
  {
    if ((c1->y + c1->s) > c2->y && (c1->y + c1->s) < (c2->y + c2->s))
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }
  else
  {
    return (0);
  }
}

int check_bottom_right_collision(t_collider* c1, t_collider* c2)
{
  if ((c1->x + c1->s) > c2->x && (c1->x + c1->s) < (c2->x + c2->s))
  {
    if ((c1->y + c1->s) > c2->y && (c1->y + c1->s) < (c2->y + c2->s))
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }
  else
  {
    return (0);
  }
}
