/*
** map.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:52:27 2016 HOVER Beckett
** Last update Thu Apr 28 15:52:31 2016 HOVER Beckett
*/
#include "client.h"

void render_tile(int position, int type, int direction)
{
  SDL_Rect rec;
  SDL_Rect crop;

  rec.x = (position % 13) * ELEMENT_SIZE;
  rec.y = (position / 13) * ELEMENT_SIZE + OFFSET;
  rec.w = ELEMENT_SIZE;
  rec.h = ELEMENT_SIZE;

  crop_texture(&crop, type, direction);
  SDL_RenderCopy(g_game->renderer, get_texture(type), &crop, &rec);
}

void render_bonus(char* c, int position)
{
  int type;

  if (get_nth_bit(c, 5) == 0)
  {
    // render lives
    type = 32;
  }
  else
  {
    // should give me :
    // 20
    // 21
    // 30
    // 31
    type = 20 + (get_nth_bit(c, 6) * 10) + get_nth_bit(c, 7);
  }

  render_tile(position, type, 0);
}

void render_block(char*c, int position)
{
  int type;

  type = 0;

  type += get_nth_bit(c, 1);
  type += get_nth_bit(c, 2);

  render_tile(position, type, 0);
}

void render_map(char* map)
{
  int i;

  for (i = 0; i < 169; i++)
  {
    render_block(&map[i], i);
    if (get_nth_bit(&map[i], 3) == 1)
    {
      render_tile(i, 3, 50 * 0);
    }
    if (get_nth_bit(&map[i], 0) == 1)
    {
      render_tile(i, 4, 50 * 0);
    }
    if (get_nth_bit(&map[i], 4) == 1)
    {
      render_bonus(&map[i], i);
    }
  }
}

void render_player_bombs(int player, int bombs, int cooldown)
{
  SDL_Rect rec;
  SDL_Rect crop;

  if (bombs == 1 && cooldown != 0)
  {
    bombs = 0;
  }

  rec.x = (player % 2) == 0 ? 70 : 580 - (bombs * 10);
  rec.y = (player < 2) ? 8 : 682;
  rec.w = bombs * 10;
  rec.h = 10;

  crop.x = 0;
  crop.y = 0;
  crop.w = bombs * 50;
  crop.h = 50;

  SDL_RenderCopy(g_game->renderer, get_texture(7), &crop, &rec);
}
