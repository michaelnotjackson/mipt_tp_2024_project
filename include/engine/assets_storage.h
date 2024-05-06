#pragma once

#include <string>
#include <unordered_map>

#include "animation.h"
#include "include/SDL/include/SDL.h"
#include "include/SDL_image/include/SDL_image.h"

class CAssetsStorage {
 public:
  std::unordered_map<std::string, SDL_Texture*> textures;
  std::unordered_map<std::string, CBaseAnimation> animations;

 public:
  CAssetsStorage();

  bool LoadTexture(const std::string& path, const std::string& name = "");

  SDL_Texture* GetTexture(const std::string& name);

  bool RegisterAnimation(CBaseAnimation animation, const std::string& name);

  CBaseAnimation& GetAnimation(const std::string& name);

  std::string GetAnimationName(const CBaseAnimation& animation);

  ~CAssetsStorage() = default;
};

extern CAssetsStorage assets_manager;