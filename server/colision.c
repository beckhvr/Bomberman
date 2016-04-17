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

int check_top_left_collision(t_collider* c1, t_collider* c2) {
  if (c1->x >= c2->x && c1->x <= (c2->x + c2->s))
  {
    if (c1->y >= c2->y && c1->y <= (c2->y + c2->s))
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

int check_top_right_collision(t_collider* c1, t_collider* c2) {
  if ((c1->x + c1->s) >= c2->x && (c1->x + c1->s) <= (c2->x + c2->s))
  {
    if (c1->y >= c2->y && c1->y <= (c2->y + c2->s))
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

int check_bottom_left_collision(t_collider* c1, t_collider* c2) {
  if (c1->x >= c2->x && c1->x <= (c2->x + c2->s))
  {
    if ((c1->y + c1->s) >= c2->y && (c1->y + c1->s) <= (c2->y + c2->s))
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

int check_bottom_right_collision(t_collider* c1, t_collider* c2) {
  if ((c1->x + c1->s) >= c2->x && (c1->x + c1->s) <= (c2->x + c2->s))
  {
    if ((c1->y + c1->s) >= c2->y && (c1->y + c1->s) <= (c2->y + c2->s))
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
