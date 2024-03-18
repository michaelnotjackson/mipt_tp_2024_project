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
class CSpecificEventStorage {
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
  CSpecificEventStorage();
};

class CTileHoverEventListener;
class CTileClickEventListener;

class CEventStorage {
 private:
  CSpecificEventStorage<CTileHoverEventListener> tile_hover_listeners;
  CSpecificEventStorage<CTileClickEventListener> tile_click_listeners;

 public:
  void RegisterCTileHoverEventListener(CTileHoverEventListener* listener);
  CSpecificEventStorage<CTileHoverEventListener>& GetTileHoverListeners();

  void RegisterCTileClickEventListener(CTileClickEventListener* listener);
  CSpecificEventStorage<CTileClickEventListener>& GetTileClickListeners();

 public:
  CTileHoverEventListener* current_hover = nullptr;
};

extern CEventStorage event_manager;