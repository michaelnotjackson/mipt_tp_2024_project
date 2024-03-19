#include <event_storage.h>

template <typename EventListenerType>
CEventListenerNode<EventListenerType>::~CEventListenerNode() {
  delete event_listener;
  delete next;
}

template <typename EventListenerType>
CSpecificEventStorage<EventListenerType>::CSpecificEventStorage()
    : highest_listener(0), listeners_count(0) {}

template <typename EventListenerType>
void CSpecificEventStorage<EventListenerType>::Register(
    EventListenerType* event_listener) {
  CEventListenerNode<EventListenerType>* new_node =
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

template <typename EventListenerType>
CEventListenerNode<EventListenerType>*
CSpecificEventStorage<EventListenerType>::GetByIndex(int idx) {
  CEventListenerNode<EventListenerType>* cur = head;

  while (cur && cur->idx != idx) {
    cur = cur->next;
  }

  return cur;
}

template <>
CEventListenerNode<CTileHoverEventListener>*
CSpecificEventStorage<CTileHoverEventListener>::GetHead() {
  return head;
}
template <>
CEventListenerNode<CTileClickEventListener>*
CSpecificEventStorage<CTileClickEventListener>::GetHead() {
  return head;
}

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

CEventStorage event_manager;