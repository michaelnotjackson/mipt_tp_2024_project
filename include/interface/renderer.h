#pragma once

#include <SDL.h>

#include <string>

SDL_Texture* LoadTexture(const std::string& file_path);

void Blit(SDL_Texture* texture, int x, int y, int fr_x = 0, int fr_y = 0,
          int fr_w = 0, int fr_h = 0);