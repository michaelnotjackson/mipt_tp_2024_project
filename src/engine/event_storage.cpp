#include "include/engine/event_storage.h"

void CEventStorage::RegisterCTileHoverEventListener(
    CTileHoverEventListener* listener) {
  tile_hover_listeners.Register(listener);
}

CSpecificEventStorage<CTileHoverEventListener>&
CEventStorage::GetTileHoverListeners() {
  return tile_hover_listeners;
}

void CEventStorage::RegisterCTileClickEventListener(
    CTileClickEventListener* listener) {
  tile_click_listeners.Register(listener);
}

CSpecificEventStorage<CTileClickEventListener>&
CEventStorage::GetTileClickListeners() {
  return tile_click_listeners;
}

void CEventStorage::Clear() {
 tile_click_listeners.Clear();
 tile_hover_listeners.Clear();
 current_hover = nullptr;
}

CEventStorage event_manager;