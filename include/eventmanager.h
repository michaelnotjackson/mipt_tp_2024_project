#pragma once

#include <mouse_eventlisteners.h>

template <typename EventListenerType>
class CEventListenerNode {
 public:
  EventListenerType* event_listener = nullptr;
  CEventListenerNode* prev = nullptr;
  CEventListenerNode* next = nullptr;

  int idx;

 public:
  ~CEventListenerNode();
};

template <typename EventListenerType>
class CSpecificEventManager {
 private:
  CEventListenerNode<EventListenerType>* head = nullptr;
  CEventListenerNode<EventListenerType>* last = nullptr;

 public:
  int highest_listener;
  int listeners_count;

 public:
  void Register(EventListenerType* event_listener);

  CEventListenerNode<EventListenerType>* GetByIndex(int idx);

  CEventListenerNode<EventListenerType>* GetHead();

 public:
  CSpecificEventManager();
};

class CEventManager {
 private:
  CSpecificEventManager<CTileHoverEventListener> tile_hover_listeners;

 public:
  void RegisterCTileHoverListener(CTileHoverEventListener* listener);
  CSpecificEventManager<CTileHoverEventListener>& GetTileHover();

 public:
  CTileHoverEventListener* current_hover = nullptr;
};

extern CEventManager event_manager;