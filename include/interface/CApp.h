#pragma once

#include <SDL.h>

class CApp {
 private:
  bool IsRunning;

 public:
  CApp();

  int OnExecute();

 public:
  bool OnInit();

  void OnEvent(SDL_Event* event);

  void OnLoop();

  void OnRender();

  void OnCleanup();
};