#include <SDL_image.h>
#include <interface/CApp.h>
#include <interface/renderer.h>
#include <animation.h>

#include <string>
#include <iostream>

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

//void Blit(SDL_Texture* texture, int x, int y, int fr_x, int fr_y, int fr_w, int fr_h) {
//  SDL_Rect dest;
//  SDL_Rect src;
//
//  dest.x = x;
//  dest.y = y;
//
//  src.x = fr_x;
//  src.y = fr_y;
//  src.w = fr_w;
//  src.h = fr_h;
//
//  SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
//
//  if (fr_w != 0 && fr_h != 0) {
//    dest.w = fr_w;
//    dest.h = fr_h;
//  }
//
//  if (SDL_RenderCopy(app.renderer, texture, &src, &dest) < 0) {
//    SDL_Log("%s", SDL_GetError());
//  }
//}