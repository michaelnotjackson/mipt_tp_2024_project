#include <SDL.h>
#include <SDL_image.h>
#include <assets_manager.h>
#include <entitylist.h>
#include <interface/CApp.h>
#include <interface/renderer.h>
#include <player.h>

CApp::CApp() : is_running(true), window(nullptr), renderer(nullptr) {}

bool CApp::LoadTextures() {
  if (!assets_manager.LoadTexture(
          "assets/Tiny "
          "Swords/Factions/Knights/Troops/Warrior/Blue/Warrior_Blue.png",
          "textures/warriors/warrior_blue")) {
    return false;
  }

  return true;
}

bool CApp::RegisterAnimations() {
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/idle")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/move")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 2, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/attack1_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 3, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/attack2_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 4, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/attack1_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 5, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/attack2_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 6, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/attack1_up")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.4),
          "animations/warriors/warrior_blue/attack2_up")) {
    return false;
  }

  return true;
}

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

  CApp::LoadTextures();
  CApp::RegisterAnimations();

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
    Blit(&cur->entity->animation, cur->entity->GetPos());
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

  entity_list.Insert(new CBasePlayer(assets_manager.GetAnimation("animations/warriors/warrior_blue/idle")));

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

CApp app;