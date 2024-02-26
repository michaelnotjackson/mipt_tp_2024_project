#include <SDL.h>
#include <interface/CApp.h>
#include <entity.h>
#include <interface/renderer.h>
#include <SDL_image.h>

#include <iostream>

CApp::CApp() : is_running(true), window(nullptr), renderer(nullptr) {}

bool CApp::OnInit() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
//  if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
//    return false;
//  }

  window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

  if (window == nullptr) {
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  if (renderer == nullptr) {
    return false;
  }

  return true;
}

void CApp::OnEvent(SDL_Event* event) {
  if (event->type == SDL_QUIT) {
    is_running = false;
  }
}

void CApp::OnCleanup() {
  SDL_Quit();
}

void CApp::OnLoop() {}

SDL_Texture* knight = nullptr;


void CApp::OnRender() {
  SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
  PosType pos(100, 100);
  Blit(knight, pos.x, pos.y);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

int CApp::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  //SDL_Init(SDL_INIT_VIDEO);
  SDL_Event event;
  knight = LoadTexture("assets/knight.png");
  if (knight == nullptr) {
    std::cout << "adsfbnvgdesrwavb ncfd";
  }

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