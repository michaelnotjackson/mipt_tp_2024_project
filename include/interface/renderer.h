#pragma once

#include <SDL.h>

#include <string>

SDL_Texture* LoadTexture(const std::string& file_path);

void Blit(SDL_Texture* texture, int x, int y);