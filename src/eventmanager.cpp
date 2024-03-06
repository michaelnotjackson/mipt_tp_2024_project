#include <eventmanager.h>

CEventListenerNode::~CEventListenerNode() {
  delete event_listener;
  delete next;
}

CEventManager::CEventManager() : highest_listener(0), listeners_count(0) {}

void CEventManager::Register(IBaseEventListener* event_listener) {
  CEventListenerNode* new_node = new CEventListenerNode();
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

CEventListenerNode* CEventManager::GetByIndex(int idx) {
  CEventListenerNode* cur = head;

  while (cur && cur->idx != idx) {
    cur = cur->next;
  }

  return cur;
}

CEventListenerNode* CEventManager::GetHead() { return head; }