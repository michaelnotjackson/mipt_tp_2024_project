#include <SDL_image.h>
#include <interface/CApp.h>
#include <interface/renderer.h>

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

void Blit(SDL_Texture* texture, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;

  SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

  if (SDL_RenderCopy(app.renderer, texture, nullptr, &dest) < 0) {
    SDL_Log("%s", SDL_GetError());
  }
}