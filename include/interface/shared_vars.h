#pragma once

#include <SDL.h>

class AppClass{
 public:
  SDL_Renderer* renderer;
  SDL_Window* window;
};

extern AppClass app;