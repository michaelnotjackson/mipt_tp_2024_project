#pragma once

#include <SDL.h>

struct CBaseAnimation {
  SDL_Texture* texture;
  SDL_Rect frame;
  int nFrames;
  uint64_t start_tick;
  int ticks_per_frame;

  CBaseAnimation(SDL_Texture* texture);
  CBaseAnimation(SDL_Texture* texture,
                 SDL_Rect frame,
                 int nFrames,
                 uint64_t start_tick,
                 int time_per_frame);

  CBaseAnimation();
};