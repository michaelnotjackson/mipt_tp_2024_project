#include "include/engine/entitylist.h"

#include "engine/globals.h"
#include "engine/room.h"
#include "include/SDL/include/SDL.h"

CEntityNode::~CEntityNode() {
  delete entity;
}

IBaseEntity* CEntityList::GetByIndex(int idx) {
  if (idx > highest_ent) {
    return nullptr;
  }

  CEntityNode* cur = head;

  while (cur != nullptr && cur->idx != idx) {
    cur = cur->next;
  }

  if (cur == nullptr) {
    return nullptr;
  }

  return cur->entity;
}

IBaseEntity* CEntityList::GetByPos(const SDL_Rect& rect) {
  CEntityNode* cur = head;

  PosType pos{rect.x, rect.y};

  while (cur != nullptr && (*cur->entity->GetPos()) != pos) {
    cur = cur->next;
  }

  return cur->entity;
}

int CEntityList::GetIndByPos(const SDL_Rect& rect) {
  CEntityNode* cur = head;

  PosType pos{rect.x, rect.y};

  while (cur != nullptr && (*cur->entity->GetPos()) != pos) {
    cur = cur->next;
  }

  return cur->idx;
}

void CEntityList::Insert(IBaseEntity* ent) {
  if (!last) {
    head = last = new CEntityNode();
  } else {
    last->next = new CEntityNode();
    last->next->prev = last;
    last = last->next;
  }

  last->entity = ent;
  last->idx = ++highest_ent;
}

void CEntityList::RemoveByIndex(int idx) {
  if (idx > highest_ent) {
    return;
  }

  CEntityNode* cur = head;

  while (cur != nullptr && cur->idx != idx) {
    cur = cur->next;
  }

  if (cur == nullptr) {
    return;
  }

  if (cur == last) {
    last = last->prev;
  }

  if (cur == head) {
    head = head->next;
  }

  if (cur->next) {
    cur->next->prev = cur->prev;
  }
  if (cur->prev) {
    cur->prev->next = cur->next;
  }
  cur->next = nullptr;
  cur->prev = nullptr;

  PosType pos = *cur->entity->GetPos();
  g_current_room.field[pos.y][pos.x]->entity_on = nullptr;

  deleted[cur->entity] = true;

  delete cur;
}

CEntityNode* CEntityList::GetHead() { return this->head; }

CEntityList::~CEntityList() {
  for (CEntityNode* node = head; node;) {
    CEntityNode* tmp = node->next;
    delete node;
    node = tmp;
  }
}

CEntityList entity_list;