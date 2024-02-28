#pragma once

#include <SDL.h>
#include <animation.h>
#include <types.h>

#include <string>

SDL_Texture* LoadTexture(const std::string& file_path);

void Blit(CBaseAnimation& anim, int x, int y);

void Blit(CBaseAnimation& anim, PosType* pos);

void AnimationCycle();