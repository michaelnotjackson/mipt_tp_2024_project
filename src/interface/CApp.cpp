#include <SDL.h>
#include <SDL_image.h>
#include <entitylist.h>
#include <interface/CApp.h>
#include <interface/renderer.h>
#include <player.h>
#include <room.h>

CApp::CApp() : is_running(true), window(nullptr), renderer(nullptr) {}

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

  return true;
}

void CApp::OnEvent(SDL_Event* event) {
  if (event->type == SDL_QUIT) {
    is_running = false;
  }
}

void CApp::OnCleanup() { SDL_Quit(); }

void CApp::OnLoop() {}

void DrawEntities() {
  CEntityNode* cur = entity_list.GetHead();

  while (cur != nullptr) {
    Blit(cur->entity->animation, cur->entity->GetPos());
    cur = cur->next;
  }
}

void CApp::OnRender() {
  SDL_RenderClear(renderer);
  DrawEntities();
  SDL_RenderPresent(renderer);
}

int CApp::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;

  SDL_Texture* texture = LoadTexture(
      "assets/Tiny "
      "Swords/Factions/Knights/Troops/Warrior/Blue/Warrior_Blue.png");

  for (int i = 0; i < 8; ++i) {
    entity_list.Insert(new CBasePlayer(CBaseAnimation(
        texture, {0, 192 * i, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4)));
    entity_list.GetByIndex(entity_list.highest_ent)->GetPos()->y =
        192 * 0.4 * i;
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