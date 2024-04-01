#pragma once

#include <string>

#include "include/SDL/include/SDL.h"
#include "include/engine/animation.h"
#include "include/engine/types.h"

SDL_Texture* LoadTexture(const std::string& file_path);

void Blit(CBaseAnimation* anim, int x, int y);

void Blit(CBaseAnimation* anim, PosType* pos);

void AnimationCycle();