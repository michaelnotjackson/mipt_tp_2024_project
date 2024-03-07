#include <SDL.h>
#include <SDL_image.h>
#include <assets_manager.h>
#include <entitylist.h>
#include <globals.h>
#include <interface/CApp.h>
#include <interface/renderer.h>
#include <player.h>
#include <room.h>
#include <utils.h>

CApp::CApp() : is_running(true), window(nullptr), renderer(nullptr) {}

Room room(SCREEN_WIDTH, SCREEN_HEIGHT);

bool CApp::LoadTextures() {
  if (!assets_manager.LoadTexture(
          "assets/Tiny "
          "Swords/Factions/Knights/Troops/Warrior/Blue/Warrior_Blue.png",
          "textures/warriors/warrior_blue")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Flat.png",
          "textures/terrain/grass")) {
    return false;
  }

  return true;
}

bool CApp::RegisterAnimations() {
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(assets_manager.GetTexture("textures/terrain/grass"),
                         SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/grass")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(assets_manager.GetTexture("textures/terrain/grass"),
                         SDL_Rect{384, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/sand")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
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

  window =
      SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  if (window == nullptr) {
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr) {
    return false;
  }

  std::atexit(CApp::OnCleanup);

  CApp::LoadTextures();
  CApp::RegisterAnimations();

  room.SetField(assets_manager.GetTexture("textures/terrain/grass"));
  g_current_room = room;
  PosType start(0, 0);
  PosType goal(2, 2);
  auto* path = FindPath(start, goal, room);

  for (auto tile : *path) {
    SDL_Log("%i%i", tile.x, tile.y);
  }

  delete path;

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
    auto* ent_pos = new PosType(PosRoomToScreen(cur->entity));
//    auto* ent_pos = new PosType(*cur->entity->GetPos());
    Blit(&cur->entity->animation, ent_pos);
    cur = cur->next;
    delete ent_pos;
  }
}

void DrawRoom(const Room& room_a) {
  int width = room_a.field[0][0]->GetTexture().frame.w *
              room_a.field[0][0]->GetTexture().scale;
  int height = room_a.field[0][0]->GetTexture().frame.h *
               room_a.field[0][0]->GetTexture().scale;
  for (int i = 0; i < SCREEN_WIDTH; i += height) {
    for (int j = 0; j < SCREEN_HEIGHT; j += width) {
      CBaseAnimation tmp =
          ((*(room_a.GetField()[i / height][j / width])).GetTexture());
      Blit(&tmp, i, j);
    }
  }
}

void CApp::OnRender() {
  SDL_RenderClear(renderer);
  DrawRoom(room);
  DrawEntities();
  SDL_RenderPresent(renderer);
}

int CApp::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;

  entity_list.Insert(new CBasePlayer(
      assets_manager.GetAnimation("animations/warriors/warrior_blue/idle")));
  entity_list.GetHead()->entity->GetPos()->x = 3;
  entity_list.GetHead()->entity->GetPos()->y = 2;

  //  entity_list.GetHead()->entity->PlayAnimation(assets_manager.GetAnimation("animations/warriors/warrior_blue/idle"));
  //  testing set animation

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