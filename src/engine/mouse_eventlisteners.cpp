#include "include/engine/mouse_eventlisteners.h"

#include <string>

#include "include/SDL/include/SDL.h"
#include "include/engine/assets_storage.h"
#include "include/engine/entitylist.h"
#include "include/engine/event_storage.h"
#include "include/engine/globals.h"
#include "include/engine/utils.h"

SDL_Rect& CTileHoverEventListener::GetRect() { return rect; }

CTileHoverEventListener::CTileHoverEventListener(const SDL_Rect& rect,
                                                 CTile* tile)
    : rect(rect), tile(tile) {}

void CTileHoverEventListener::notify() {
  std::string name =
      assets_manager.GetAnimationName(tile->GetTexture()) + "_hovered";

  tile->SetTexture(assets_manager.GetAnimation(name));

  PosType pos = GetTilePos(tile, g_current_room);
}

void CTileHoverEventListener::reset() {
  std::string name = assets_manager.GetAnimationName(tile->GetTexture());

  if (name.find("_hovered") != std::string::npos) {
    tile->SetTexture(
        assets_manager.GetAnimation(name.substr(0, name.length() - 8)));
  }
}

CTile* CTileHoverEventListener::GetTile() { return tile; }

CTileClickEventListener::CTileClickEventListener(const SDL_Rect& rect,
                                                 CTile* tile)
    : rect(rect), tile(tile) {}

SDL_Rect& CTileClickEventListener::GetRect() { return rect; }

void CTileClickEventListener::notify() {
  g_current_executor->MoveBy(&g_current_path);
}