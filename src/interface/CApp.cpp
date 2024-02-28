#include <SDL.h>
#include <SDL_image.h>
#include <entity.h>
#include <interface/CApp.h>
#include <interface/renderer.h>
#include <room.h>

#include <iostream>

CApp::CApp() : is_running(true), window(nullptr), renderer(nullptr) {}

SDL_Texture* grass = nullptr;
Room room(720, 720);

bool CApp::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
    return false;
  }

  window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 720, 720, 0);

  if (window == nullptr) {
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    return false;
  }

  room.SetField();

  return true;
}

void CApp::OnEvent(SDL_Event* event) {
  if (event->type == SDL_QUIT) {
    is_running = false;
  }
}

void CApp::OnCleanup() { SDL_Quit(); }

void CApp::OnLoop() {}

SDL_Texture* knight = nullptr;

void CApp::OnRender() {
  SDL_RenderClear(renderer);
  //SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  //PosType pos(100, 100);
  //Blit(knight, pos.x, pos.y);
  room.DrawField(grass);
  SDL_RenderPresent(renderer);
}

int CApp::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;
  grass = LoadTexture("assets/Tiny Swords/Terrain/Ground/Tilemap_Flat.png");

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }

    OnLoop();
    OnRender();

    SDL_Delay(16);
  }

  OnCleanup();

  return 0;
}