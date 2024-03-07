#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <animation.h>

#include <string>
#include <unordered_map>

class CAssetsManager {
 private:
  std::unordered_map<std::string, SDL_Texture*> textures;
  std::unordered_map<std::string, CBaseAnimation> animations;

 public:
  CAssetsManager();

  bool LoadTexture(const std::string& path, const std::string& name = "");

  SDL_Texture* GetTexture(const std::string& name);

  bool RegisterAnimation(CBaseAnimation animation, const std::string& name);

  CBaseAnimation& GetAnimation(const std::string& name);

  std::string GetAnimationName(const CBaseAnimation& animation);

  ~CAssetsManager() = default;
};

extern CAssetsManager assets_manager;