#pragma once

#include <SDL.h>
#include <animation.h>

#include <string>

SDL_Texture* LoadTexture(const std::string& file_path);

void Blit(CBaseAnimation& anim, int x, int y);