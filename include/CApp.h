#pragma once

#include "include/SDL/include/SDL.h"
#include <fstream>

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
  bool OnInit();

  void OnEvent(SDL_Event* event);

  void OnLoop();

  void OnRender();

  static void OnCleanup();
};

extern CApp app;

void UpdateListeners();

void SwitchRoom();