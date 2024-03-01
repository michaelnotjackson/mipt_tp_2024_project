#include <SDL.h>
#include <SDL_image.h>
#include <animation.h>
#include <assets_manager.h>
#include <interface/CApp.h>

CAssetsManager::CAssetsManager() : textures() {}

bool CAssetsManager::LoadTexture(const std::string& path,
                                 const std::string& name) {
  SDL_Texture* texture = IMG_LoadTexture(app.renderer, path.c_str());

  if (texture == nullptr) {
    SDL_Log("%s", SDL_GetError());
    return false;
  }

  if (name.empty()) {
    textures[path] = texture;
    return true;
  }

  textures[name] = texture;
  return true;
}

SDL_Texture* CAssetsManager::GetTexture(const std::string& name) {
  return textures[name];
}

bool CAssetsManager::RegisterAnimation(CBaseAnimation* animation,
                                       const std::string& name) {
  if (animations.find(name) != animations.end()) {
    SDL_LogError(1, "%s",
                 "ERROR: Trying to register animation with name that was "
                 "already taken");
    return false;
  }

  animations[name] = animation;

  return true;
}

CBaseAnimation* CAssetsManager::GetAnimation(const std::string& name) {
  return animations[name];
}

CAssetsManager::~CAssetsManager() {
  for (auto &[name, animation]: animations) {
    delete animation;
  }
}

CAssetsManager assets_manager;