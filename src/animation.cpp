#include <SDL.h>
#include <animation.h>

CBaseAnimation::CBaseAnimation(SDL_Texture* texture)
    : texture(texture),
      frame{0, 0, 0, 0},
      nFrames(1),
      ticks_per_frame(100),
      start_tick(SDL_GetTicks64()) {}

CBaseAnimation::CBaseAnimation(SDL_Texture* texture, SDL_Rect frame,
                               int nFrames, uint64_t start_tick,
                               int time_per_frame)
    : texture(texture),
      frame(frame),
      nFrames(nFrames),
      start_tick(start_tick),
      ticks_per_frame(time_per_frame) {}

CBaseAnimation::CBaseAnimation()
    : texture(nullptr),
      frame{0, 0},
      nFrames(1),
      ticks_per_frame(100),
      start_tick(SDL_GetTicks64()) {}