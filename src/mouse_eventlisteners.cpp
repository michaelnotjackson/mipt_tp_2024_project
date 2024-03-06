#include <SDL.h>
#include <assets_manager.h>
#include <entitylist.h>
#include <globals.h>
#include <mouse_eventlisteners.h>

SDL_Rect& CTileHoverEventListener::GetRect() { return rect; }

CTileHoverEventListener::CTileHoverEventListener(const SDL_Rect& rect,
                                                 CTile* tile)
    : rect(rect), tile(tile) {}

void CTileHoverEventListener::notify() {
  std::string name = assets_manager.GetAnimationName(tile->GetTexture());

  tile->SetTexture(assets_manager.GetAnimation(name + "_hovered"));

  int x, y;
  SDL_GetMouseState(&x, &y);

  PosType tile_pos = GetTilePos(tile, g_current_room);
  int width = tile->GetTexture().frame.w * tile->GetTexture().scale;
  int height = tile->GetTexture().frame.h * tile->GetTexture().scale;

  while (x >= tile_pos.x && y >= tile_pos.y && x <= width && y <= height) {
    SDL_GetMouseState(&x, &y);
  }

  tile->SetTexture(assets_manager.GetAnimation(name));
}