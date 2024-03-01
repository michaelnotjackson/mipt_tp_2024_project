#include <SDL_image.h>
#include <animation.h>
#include <interface/CApp.h>
#include <interface/renderer.h>

#include <string>

SDL_Texture* LoadTexture(const std::string& file_path) {
  SDL_Texture* texture = nullptr;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", file_path.c_str());

  texture = IMG_LoadTexture(app.renderer, file_path.c_str());

  if (texture == nullptr) {
    SDL_LogError(0, "%s", SDL_GetError());
  }

  return texture;
}

void Blit(CBaseAnimation* anim, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;

  dest.w = anim->frame.w * anim->scale;
  dest.h = anim->frame.h * anim->scale;

  SDL_Rect src = anim->frame;
  src.x +=
      src.w * (((SDL_GetTicks64() - anim->start_tick) / anim->ticks_per_frame) %
               anim->nFrames);

  if (SDL_RenderCopy(app.renderer, anim->texture, &src, &dest) < 0) {
    SDL_Log("%s", SDL_GetError());
  }
}

void Blit(CBaseAnimation* anim, PosType* pos) { Blit(anim, pos->x, pos->y); }