#pragma once

#include "include/SDL/include/SDL.h"

class CApp {
 private:
  bool is_running;

 public:
  SDL_Window* window;
  SDL_Renderer* renderer;

 public:
  CApp();

  int OnExecute();

 public:
  void RenderLoop();

  bool OnInit();

  void OnEvent(SDL_Event* event);

  void OnLoop();

  void OnRender();

  static void OnCleanup();
};

extern CApp app;