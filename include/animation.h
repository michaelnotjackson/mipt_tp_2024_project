#pragma once

#include <SDL.h>

class CBaseAnimation {
 public:
  SDL_Texture* texture{};
  SDL_Rect frame{};
  int nFrames{};
  uint64_t start_tick{};
  int ticks_per_frame{};
  double scale{};

 public:
  explicit CBaseAnimation(SDL_Texture* texture);
  CBaseAnimation(SDL_Texture* texture, SDL_Rect frame, int nFrames,
                 uint64_t start_tick, int time_per_frame, double scale = 1.0);

  CBaseAnimation();

  CBaseAnimation(CBaseAnimation const& other) = default;

 public:
  void ResetTiming();

 public:
  bool operator==(const CBaseAnimation& other) const;
  bool operator!=(const CBaseAnimation& other) const;
};