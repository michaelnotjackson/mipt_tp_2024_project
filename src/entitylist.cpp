#include <entitylist.h>

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

void CEntityList::Insert(IBaseEntity* ent) {
  last->next = new CEntityNode();
  last->next->prev = last;
  last = last->next;

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

  if (cur == head) {
    head = head->next;
    delete cur;
    return;
  }

  cur->prev->next = cur->next;
  cur->next->prev = cur->prev;

  delete cur;
}

int CEntityList::EntityCount() { return ent_count; }

CEntityNode* CEntityList::GetHead() { return this->head; }

CEntityList entity_list;