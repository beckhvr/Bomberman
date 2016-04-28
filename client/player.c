/*
** player.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:53:03 2016 HOVER Beckett
** Last update Thu Apr 28 15:53:07 2016 HOVER Beckett
*/
#include "client.h"

void render_players(t_player_info players[4])
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (players[i].playing == 1)
    {
      if (players[i].hp > 0)
      {
        render_player(i + 10, players[i].x, players[i].y, players[i].direction);
        render_player_bombs(i, players[i].bombs, players[i].cooldown);
      }
      render_player_hp(i, players[i].hp);
    }
  }
}

void render_player(int type, int x, int y, int direction)
{
  SDL_Rect rec;
  SDL_Rect crop;

  rec.x = x - 5;
  rec.y = y - 5 + OFFSET;
  rec.w = PLAYER_SIZE;
  rec.h = PLAYER_SIZE;

  crop_texture(&crop, type, direction);
  SDL_RenderCopy(g_game->renderer, get_texture(type), &crop, &rec);
}

void render_player_hp(int player, int hp)
{
  int x;
  int y;
  SDL_Rect rec;
  SDL_Rect crop;

  rec.x = (player % 2) == 0 ? 10 : 585;
  rec.y = (player < 2) ? 8 : 682;
  rec.w = 60;
  rec.h = 10;

  crop.x = 0;
  crop.y = hp * 50;
  crop.w = 300;
  crop.h = 50;

  SDL_RenderCopy(g_game->renderer, get_texture(6), &crop, &rec);
}
