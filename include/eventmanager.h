#pragma once

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

class CTileHoverEventListener;
class CTileClickEventListener;

class CEventManager {
 private:
  CSpecificEventManager<CTileHoverEventListener> tile_hover_listeners;
  CSpecificEventManager<CTileClickEventListener> tile_click_listeners;

 public:
  void RegisterCTileHoverEventListener(CTileHoverEventListener* listener);
  CSpecificEventManager<CTileHoverEventListener>& GetTileHoverListeners();

  void RegisterCTileClickEventListener(CTileClickEventListener* listener);
  CSpecificEventManager<CTileClickEventListener>& GetTileClickListeners();

 public:
  CTileHoverEventListener* current_hover = nullptr;
};

extern CEventManager event_manager;