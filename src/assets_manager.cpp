#include <SDL.h>
#include <SDL_image.h>
#include <assets_manager.h>
#include <interface/CApp.h>

CAssetsManager::CAssetsManager() : textures() {}

void CAssetsManager::LoadTexture(const std::string& path,
                                 const std::string& name) {
  SDL_Texture* texture = IMG_LoadTexture(app.renderer, path.c_str());

  if (name.empty()) {
    textures[path] = texture;
    return;
  }

  textures[name] = texture;
}

inline SDL_Texture* CAssetsManager::GetTexture(const std::string& name) {
  return textures[name];
}