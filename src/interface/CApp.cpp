#include <SDL.h>
#include <SDL_image.h>
#include <assets_manager.h>
#include <entitylist.h>
#include <eventmanager.h>
#include <globals.h>
#include <interface/CApp.h>
#include <interface/renderer.h>
#include <mouse_eventlisteners.h>
#include <player.h>
#include <room.h>
#include <utils.h>

#include <iostream>

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

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Flat_Hovered.png",
          "textures/terrain/grass_hovered")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Elevation.png",
          "textures/terrain/wall")) {
    return false;
  }

  if (!assets_manager.LoadTexture(
          "assets/Tiny Swords/Terrain/Ground/Tilemap_Elevation_Hovered.png",
          "textures/terrain/wall_hovered")) {
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
          CBaseAnimation(
              assets_manager.GetTexture("textures/terrain/grass_hovered"),
              SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/grass_hovered")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(assets_manager.GetTexture("textures/terrain/wall"),
                         SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/wall")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/terrain/wall_hovered"),
              SDL_Rect{64, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/wall_hovered")) {
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
              assets_manager.GetTexture("textures/terrain/grass_hovered"),
              SDL_Rect{384, 64, 64, 64}, 1, SDL_GetTicks64(), 1, 1),
          "animations/terrain/sand_hovered")) {
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
              SDL_Rect{0, 192, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/move")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 2, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack1_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 3, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack2_right")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 4, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack1_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 5, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack2_down")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 192 * 6, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
          "animations/warriors/warrior_blue/attack1_up")) {
    return false;
  }
  if (!assets_manager.RegisterAnimation(
          CBaseAnimation(
              assets_manager.GetTexture("textures/warriors/warrior_blue"),
              SDL_Rect{0, 0, 192, 192}, 6, SDL_GetTicks64(), 100, 0.5),
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

  room.SetField();
  g_current_room = room;

  CTile* tile = room.GetField()[0][0];
  int width = tile->GetTexture().frame.w * tile->GetTexture().scale;
  int height = tile->GetTexture().frame.h * tile->GetTexture().scale;
  SDL_Rect rect;
  rect.w = width;
  rect.h = height;
  for (int i = 0; i < room.GetField().size(); i++) {
    for (int j = 0; j < room.GetField()[0].size(); j++) {
      rect.x = j * width;
      rect.y = i * height;
      event_manager.RegisterCTileHoverEventListener(
          new CTileHoverEventListener(rect, room.GetField()[i][j]));
      event_manager.RegisterCTileClickEventListener(
          new CTileClickEventListener(rect, room.GetField()[i][j]));
    }
  }

  g_current_executor = g_turnmanager.GetExecutor();

  return true;
}

bool CheckRect(const SDL_Rect& rect, int x, int y) {
  return !(x < rect.x || y < rect.y || x > rect.x + rect.w ||
           y > rect.y + rect.h);
}

void CApp::OnEvent(SDL_Event* event) {
  if (event->type == SDL_QUIT) {
    is_running = false;
    return;
  }
  if (event->type == SDL_KEYDOWN) {
    entity_list.GetHead()->entity->PlayAnimation(assets_manager.GetAnimation(
        "animations/warriors/warrior_blue/attack2_down"));
  }
  if (event->type == SDL_MOUSEMOTION) {
    int x = event->motion.x, y = event->motion.y;

    if (event_manager.current_hover != nullptr &&
        CheckRect(event_manager.current_hover->GetRect(), x, y) &&
        !g_current_path.empty()) {
      goto MOUSEMOTIONEND;
    }

    if (event_manager.current_hover != nullptr) {
      event_manager.current_hover->reset();
    }

    auto* cur = event_manager.GetTileHoverListeners().GetHead();
    while (cur != nullptr) {
      if (CheckRect(cur->event_listener->GetRect(), x, y)) {
        cur->event_listener->notify();
        break;
      }
      cur = cur->next;
    }

    event_manager.current_hover = cur->event_listener;

    if (g_current_action == ActionType::MOVE) {
      std::vector<PosType>* tmp_path =
          FindPath(*g_current_executor->GetPos(),
                   GetTilePos(cur->event_listener->GetTile(), g_current_room));

      if (!tmp_path) {
        g_current_path.clear();
      } else {
        g_current_path.assign(tmp_path->begin(), tmp_path->end());
      }
    }
  }
MOUSEMOTIONEND:
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    int x = event->button.x, y = event->button.y;
    if (g_current_action == ActionType::WAIT) {
      goto MOUSEBUTTONDOWNEND;
    }

    if (event->button.button == SDL_BUTTON_LEFT) {
      auto* cur = event_manager.GetTileClickListeners().GetHead();
      while (cur != nullptr) {
        if (CheckRect(cur->event_listener->GetRect(), x, y)) {
          cur->event_listener->notify();
          break;
        }
        cur = cur->next;
      }
    }
  }
MOUSEBUTTONDOWNEND:;
}

void CApp::OnCleanup() { SDL_Quit(); }

void CApp::OnLoop() {
  if (g_move_in_process) {
    g_current_action = ActionType::WAIT;
  }
  if (g_current_action == ActionType::WAIT && !g_move_in_process) {
    g_current_action = ActionType::MOVE;
    if (g_current_path.empty()) {
      std::vector<PosType>* tmp_path =
          FindPath(*g_current_executor->GetPos(),
                   GetTilePos(event_manager.current_hover->GetTile(), g_current_room));

      if (!tmp_path) {
        g_current_path.clear();
      } else {
        g_current_path.assign(tmp_path->begin(), tmp_path->end());
      }
    }
  }
}

void DrawEntities() {
  CEntityNode* cur = entity_list.GetHead();

  while (cur != nullptr) {
    auto* ent_pos = new PosType(EntityPosRoomToScreen(cur->entity));
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
  for (int i = 0; i < SCREEN_HEIGHT; i += height) {
    for (int j = 0; j < SCREEN_WIDTH; j += width) {
      CBaseAnimation tmp =
          room_a.GetField()[i / height][j / width]->GetTexture();
      Blit(&tmp, j, i);
    }
  }
}

void DrawPath() {
  if (g_current_action != ActionType::MOVE) {
    return;
  }

  if (!g_current_executor) {
    return;
  }

  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);

  SDL_Point start = PointRoomToScreenTileCenter(*g_current_executor->GetPos());

  auto* path = new SDL_Point[g_current_path.size() + 1];
  path[0] = start;

  for (int i = 0; i < g_current_path.size(); ++i) {
    path[i + 1] = PointRoomToScreenTileCenter(g_current_path[i]);
  }

  SDL_RenderDrawLines(app.renderer, path, g_current_path.size() + 1);

  delete[] path;
}

void CApp::OnRender() {
  SDL_RenderClear(renderer);
  DrawRoom(room);
  DrawEntities();
  DrawPath();
  SDL_RenderPresent(renderer);
}

int CApp::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;

  entity_list.Insert(new CBasePlayer(
      assets_manager.GetAnimation("animations/warriors/warrior_blue/idle")));

  g_turnmanager.ShiftTurn();
  g_turnmanager.ResetTurns();

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