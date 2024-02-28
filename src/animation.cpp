#include <SDL.h>
#include <animation.h>

CBaseAnimation::CBaseAnimation(SDL_Texture *texture)
    : texture(texture), frame{0, 0, 0, 0}, nFrames(1), show_time(0) {}

CBaseAnimation::CBaseAnimation(SDL_Texture *texture,
                               SDL_Rect frame,
                               int nFrames,
                               int show_time)
                               : texture(texture),
                                 frame(frame),
                                 nFrames(nFrames),
                                 show_time(show_time){};

CBaseAnimation::CBaseAnimation(): texture(), frame(), nFrames(0), show_time(0) {};