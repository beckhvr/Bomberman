/*
** texture.c for Bomberman in /Users/becketthover/Desktop/Bomberman
**
** Made by HOVER Beckett
** Login   <hover_b@etna-alternance.net>
**
** Started on  Thu Apr 28 15:53:41 2016 HOVER Beckett
** Last update Thu Apr 28 15:53:45 2016 HOVER Beckett
*/
#include "client.h"

int init_textures()
{
  int i;

  for (i = 0; i < 14; i++)
  {
    g_game->textures[i] = NULL;
  }

  g_game->textures[0] = IMG_LoadTexture(g_game->renderer, "../img/elements.png");
  g_game->textures[6] = IMG_LoadTexture(g_game->renderer, "../img/lives.png");
  g_game->textures[7] = IMG_LoadTexture(g_game->renderer, "../img/bombs.png");
  g_game->textures[8] = IMG_LoadTexture(g_game->renderer, "../img/bonus.png");
  g_game->textures[10] = IMG_LoadTexture(g_game->renderer, "../img/player1.png");
  g_game->textures[11] = IMG_LoadTexture(g_game->renderer, "../img/player2.png");
  g_game->textures[12] = IMG_LoadTexture(g_game->renderer, "../img/player3.png");
  g_game->textures[13] = IMG_LoadTexture(g_game->renderer, "../img/player4.png");

  return (0);
}

void free_textures()
{
  int i;

  for (i = 0; i < 14; i++)
  {
    if (g_game->textures[i] != NULL)
    {
      SDL_DestroyTexture(g_game->textures[i]);
    }
  }
}

void crop_texture(SDL_Rect* crop, int type, int offset)
{
  int i;

  i = ((SDL_GetTicks() - g_game->timer) / 100) % 4;
  crop->x = 50 * type;
  crop->y = offset * 50;
  crop->w = 50;
  crop->h = 50;

  if (type > 2)
  {
    crop->y = 50 * (i);
  }
  if (type > 9 && type < 20)
  {
    crop->x = 50 * offset;
  }

  if (type > 19)
  {
    crop->x = (type % 10) * 50;
    crop->y = (type / 10) * 50;
  }
}

SDL_Texture* get_texture(int type)
{
  if (type < 5)
  {
    return g_game->textures[0];
  }
  if (type > 19)
  {
    return g_game->textures[8];
  }

  return g_game->textures[type];
}
