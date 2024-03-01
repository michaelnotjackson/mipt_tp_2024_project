#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <unordered_map>

class CAssetsManager {
 private:
  std::unordered_map<std::string, SDL_Texture*> textures;

 public:
  CAssetsManager();

  void LoadTexture(const std::string& path, const std::string& name = "");

  inline SDL_Texture* GetTexture(const std::string& name);
};