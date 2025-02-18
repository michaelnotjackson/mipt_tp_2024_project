#pragma once

#include "base_eventlistener.h"
#include "entity.h"
#include "include/SDL/include/SDL.h"
#include "room.h"

enum class HoverTarget { TILE, UI };

class IBaseMouseEventListener : public IBaseEventListener {
 public:
  HoverTarget target;
};

class CTileHoverEventListener : public IBaseMouseEventListener {
  SDL_Rect rect;
  CTile* tile;

 public:
  static const HoverTarget target = HoverTarget::TILE;

 public:
  virtual void notify() final;
  virtual void reset() final;

  SDL_Rect& GetRect();
  CTile* GetTile();

 public:
  CTileHoverEventListener(const SDL_Rect& rect, CTile* tile);

  CTileHoverEventListener() = delete;
};

class CTileClickEventListener : public IBaseMouseEventListener {
  SDL_Rect rect;
  CTile* tile;

 public:
  static const HoverTarget target = HoverTarget::TILE;

 public:
  virtual void notify() final;
  virtual void reset() final {}

  SDL_Rect& GetRect();

 public:
  CTileClickEventListener(const SDL_Rect& rect, CTile* tile);

  CTileClickEventListener() = delete;
};