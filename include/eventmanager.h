#pragma once

#include <base_eventlistener.h>

class CEventListenerNode {
 public:
  IBaseEventListener* event_listener = nullptr;
  CEventListenerNode* prev = nullptr;
  CEventListenerNode* next = nullptr;

  int idx;

 public:
  ~CEventListenerNode();
};

class CEventManager {
 private:
  CEventListenerNode* head = nullptr;
  CEventListenerNode* last = nullptr;

 public:
  int highest_listener;
  int listeners_count;

 public:
  void Register(IBaseEventListener* event_listener);

  CEventListenerNode* GetByIndex(int idx);

  CEventListenerNode* GetHead();

 public:
  CEventManager();
};