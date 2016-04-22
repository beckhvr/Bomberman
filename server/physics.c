/*
** physics.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Fri Apr 22 07:27:00 2016 HOVER Beckett
** Last update Fri Apr 22 07:27:05 2016 HOVER Beckett
*/
#include "server.h"

int get_left_range(int point, int increments)
{
  int i;

  i = 0;
  while (point > i * increments)
  {
    i++;
  }

  return (i - 1) * increments;
}
