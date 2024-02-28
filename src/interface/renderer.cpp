#include <SDL_image.h>
#include <animation.h>
#include <interface/CApp.h>
#include <interface/renderer.h>

#include <iostream>
#include <string>

SDL_Texture* LoadTexture(const std::string& file_path) {
  SDL_Texture* texture = nullptr;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", file_path.c_str());

  if (app.window == nullptr) {
    std::cout << "aboba";
  }

  texture = IMG_LoadTexture(app.renderer, file_path.c_str());

  return texture;
}

void Blit(CBaseAnimation& anim, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;

  dest.w = anim.frame.w;
  dest.h = anim.frame.h;

  if (SDL_RenderCopy(app.renderer, anim.texture, &anim.frame, &dest) < 0) {
    SDL_Log("%s", SDL_GetError());
  }
}

void Blit(CBaseAnimation& anim, PosType* pos) {
  Blit(anim, pos->x, pos->y);
}