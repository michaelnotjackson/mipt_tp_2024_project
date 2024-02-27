#include <SDL.h>
#include <animation.h>

CBaseAnimation::CBaseAnimation(SDL_Texture* texture)
    : texture(texture), frame{0, 0, 0, 0}, nFrames(1), show_time(0) {}