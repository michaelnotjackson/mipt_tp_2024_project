#include <SDL.h>
#include <SDL_image.h>
#include <animation.h>
#include <assets_storage.h>
#include <interface/CApp.h>

CAssetsStorage::CAssetsStorage() : textures() {}

bool CAssetsStorage::LoadTexture(const std::string& path,
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

SDL_Texture* CAssetsStorage::GetTexture(const std::string& name) {
  return textures[name];
}

bool CAssetsStorage::RegisterAnimation(CBaseAnimation animation,
                                       const std::string& name) {
  if (animations.find(name) != animations.end()) {
    SDL_LogError(1, "%s",
                 "ERROR: Trying to register animation with name that was "
                 "already taken");
    return false;
  }

  animations[name] = std::move(animation);

  return true;
}

CBaseAnimation& CAssetsStorage::GetAnimation(const std::string& name) {
  return animations[name];
}

std::string CAssetsStorage::GetAnimationName(const CBaseAnimation& animation) {
  for (auto &[k, v]: animations) {
    if (v == animation) {
      return k;
    }
  }

  return "";
}

CAssetsStorage assets_manager;