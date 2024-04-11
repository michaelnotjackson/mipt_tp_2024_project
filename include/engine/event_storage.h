#pragma once

template<typename EventListenerType>
class CEventListenerNode {
 public:
  EventListenerType *event_listener = nullptr;
  CEventListenerNode *prev = nullptr;
  CEventListenerNode *next = nullptr;

  int idx;

 public:
  ~CEventListenerNode() {
    delete event_listener;
    delete next;
  }
};

template<typename EventListenerType>
class CSpecificEventStorage {
 private:
  CEventListenerNode<EventListenerType> *head = nullptr;
  CEventListenerNode<EventListenerType> *last = nullptr;

 public:
  int highest_listener;
  int listeners_count;

 public:
  void Register(
      EventListenerType *event_listener) {
    auto *new_node =
        new CEventListenerNode<EventListenerType>();
    new_node->event_listener = event_listener;
    new_node->idx = ++highest_listener;

    if (head == nullptr) {
      head = last = new_node;
      return;
    }

    last->next = new_node;
    new_node->prev = last;
    last = new_node;
  }


  CEventListenerNode<EventListenerType> *GetByIndex(int idx) {
    CEventListenerNode<EventListenerType> *cur = head;

    while (cur && cur->idx != idx) {
      cur = cur->next;
    }

    return cur;
  }

  CEventListenerNode<EventListenerType> *GetHead() { return head; }

  void Clear() {
    delete head;
    head = nullptr;
    last = nullptr;
    highest_listener = 0;
    listeners_count = 0;
  }

 public:
  CSpecificEventStorage() = default;
};

class CTileHoverEventListener;

class CTileClickEventListener;

class CEventStorage {
 private:
  CSpecificEventStorage<CTileHoverEventListener> tile_hover_listeners;
  CSpecificEventStorage<CTileClickEventListener> tile_click_listeners;

 public:
  void RegisterCTileHoverEventListener(CTileHoverEventListener *listener);

  CSpecificEventStorage<CTileHoverEventListener> &GetTileHoverListeners();

  void RegisterCTileClickEventListener(CTileClickEventListener *listener);

  CSpecificEventStorage<CTileClickEventListener> &GetTileClickListeners();

 public:
  CTileHoverEventListener *current_hover = nullptr;

  void Clear();
};

extern CEventStorage event_manager;