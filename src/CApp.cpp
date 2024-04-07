#include "include/CApp.h"

#include <engine/engine_init.h>

#include <thread>

#include "include/SDL_image/include/SDL_image.h"
#include "include/engine/assets_storage.h"
#include "include/engine/entitylist.h"
#include "include/engine/event_storage.h"
#include "include/engine/globals.h"
#include "include/engine/mouse_eventlisteners.h"
#include "include/engine/player.h"
#include "include/engine/renderer.h"
#include "include/engine/utils.h"

CApp::CApp() : is_running(true), window(nullptr), renderer(nullptr) {}

Room room(SCREEN_WIDTH, SCREEN_HEIGHT);  // NOLINT

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

  EngineInitTextures();
  EngineInitAnimations();

  room.SetField();
  g_current_room = room;

  CTile* tile = room.GetField()[0][0];
  int width = tile->GetTexture().frame.w * tile->GetTexture().scale;   // NOLINT
  int height = tile->GetTexture().frame.h * tile->GetTexture().scale;  // NOLINT
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
    if (event->key.keysym.sym == SDLK_SPACE) {
      if (g_current_action == ActionType::BUSY) {
        goto KEYDOWNEND;
      }
      g_turnmanager.ShiftTurn();

      if (g_current_action == ActionType::FREE) {
        std::vector<PosType>* tmp_path = FindPath(
            *g_current_executor->GetPos(),
            GetTilePos(event_manager.current_hover->GetTile(), g_current_room));

        if (!tmp_path) {
          g_current_path.clear();
        } else {
          g_current_path.assign(tmp_path->begin(), tmp_path->end());
        }
      }
    }
  }
KEYDOWNEND:;
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

    if (cur != nullptr) {
      event_manager.current_hover = cur->event_listener;
    } else if (event_manager.current_hover == nullptr) {
      event_manager.current_hover =
          event_manager.GetTileHoverListeners().GetHead()->event_listener;
    }

    if (g_current_action == ActionType::FREE) {
      RecalculatePath();
    }
  }
MOUSEMOTIONEND:
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    int x = event->button.x, y = event->button.y;
    if (g_current_action == ActionType::BUSY) {
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
    if (event->button.button == SDL_BUTTON_RIGHT) {
      auto enemy_pos = GetTilePos(event_manager.current_hover->GetTile(), g_current_room);
      if (g_current_room.field[enemy_pos.y][enemy_pos.x]->entity_on == nullptr) {
        goto MOUSEBUTTONDOWNEND;
      }
      g_current_action = ActionType::BUSY;
      g_current_executor->MoveBy(&g_current_path);
      g_current_executor->Attack(enemy_pos);
    }
  }
MOUSEBUTTONDOWNEND:;
}

void CApp::OnCleanup() { SDL_Quit(); }

void CApp::OnLoop() {
  if (g_move_in_process) {
    g_current_action = ActionType::BUSY;
  }
  if (g_current_action == ActionType::BUSY && !g_move_in_process) {
    g_current_action = ActionType::FREE;
    if (g_current_path.empty()) {
      std::vector<PosType>* tmp_path = FindPath(
          *g_current_executor->GetPos(),
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
  int width = room_a.field[0][0]->GetTexture().frame.w *  // NOLINT
              room_a.field[0][0]->GetTexture().scale;
  int height = room_a.field[0][0]->GetTexture().frame.h *  // NOLINT
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
  if (g_current_action != ActionType::FREE) {
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

  SDL_RenderDrawLines(app.renderer, path, g_current_path.size() + 1);  // NOLINT

  delete[] path;
}

void CApp::OnRender() {
  SDL_RenderClear(renderer);
  DrawRoom(room);
  DrawEntities();
  DrawPath();
  SDL_RenderPresent(renderer);
}

void CApp::RenderLoop() {
  while (is_running) {
    OnRender();
  }
}

int CApp::OnExecute() {
  if (!OnInit()) {
    return -1;
  }

  SDL_Event event;

  entity_list.Insert(new CBasePlayer(
      assets_manager.GetAnimation("animations/warriors/warrior_blue/idle")));
  entity_list.Insert(new CBasePlayer(
      assets_manager.GetAnimation("animations/warriors/warrior_blue/idle")));

  entity_list.Insert(new CBasePlayer(
      assets_manager.GetAnimation("animations/warriors/warrior_red/idle")));

  g_turnmanager.ShiftTurn();
  g_turnmanager.ResetTurns();

  std::thread render_thread(&CApp::RenderLoop, this);

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }

    OnLoop();

    SDL_Delay(16);
  }

  render_thread.join();
  OnCleanup();

  return 0;
}

CApp app;