#include <SDL.h>
#include <animation.h>

#include <memory>

CBaseAnimation::CBaseAnimation(SDL_Texture* texture)
    : texture(texture),
      frame{0, 0, 0, 0},
      nFrames(1),
      ticks_per_frame(100),
      start_tick(SDL_GetTicks64()),
      scale(1) {}

CBaseAnimation::CBaseAnimation(SDL_Texture* texture, SDL_Rect frame,
                               int nFrames, uint64_t start_tick,
                               int time_per_frame, double scale)
    : texture(texture),
      frame(frame),
      nFrames(nFrames),
      start_tick(start_tick),
      ticks_per_frame(time_per_frame),
      scale(scale) {}

CBaseAnimation::CBaseAnimation()
    : texture(nullptr),
      frame{0, 0},
      nFrames(1),
      ticks_per_frame(100),
      start_tick(SDL_GetTicks64()),
      scale(1) {}

void CBaseAnimation::ResetTiming() { start_tick = SDL_GetTicks64(); }