#pragma once

#include <SDL.h>

struct CBaseAnimation {
  SDL_Texture* texture;
  SDL_Rect frame;
  int nFrames;
  int show_time;

  CBaseAnimation(SDL_Texture* texture);
  CBaseAnimation(SDL_Texture* texture,
                 SDL_Rect frame,
                 int nFrames,
                 int show_time);
};