#include <eventmanager.h>

template <typename EventListenerType>
CEventListenerNode<EventListenerType>::~CEventListenerNode() {
  delete event_listener;
  delete next;
}

template <typename EventListenerType>
CSpecificEventManager<EventListenerType>::CSpecificEventManager() : highest_listener(0), listeners_count(0) {}

template <typename EventListenerType>
void CSpecificEventManager<EventListenerType>::Register(EventListenerType* event_listener) {
  CEventListenerNode<EventListenerType>* new_node = new CEventListenerNode<EventListenerType>();
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

template <typename EventListenerType>
CEventListenerNode<EventListenerType>* CSpecificEventManager<EventListenerType>::GetByIndex(int idx) {
  CEventListenerNode<EventListenerType>* cur = head;

  while (cur && cur->idx != idx) {
    cur = cur->next;
  }

  return cur;
}

template<> CEventListenerNode<CTileHoverEventListener> *CSpecificEventManager<CTileHoverEventListener>::GetHead() { return head; }

void CEventManager::RegisterCTileHoverListener(CTileHoverEventListener* listener) {
  tile_hover_listeners.Register(listener);
}

CSpecificEventManager<CTileHoverEventListener>& CEventManager::GetTileHover() { return tile_hover_listeners; }

CEventManager event_manager;