#pragma once

#include <entity.h>

#include <string>

class CEntityNode {
 public:
  IBaseEntity* entity = nullptr;
  CEntityNode* next = nullptr;
  CEntityNode* prev = nullptr;
  int idx;

 public:
  ~CEntityNode();
};

class CEntityList {
 private:
  CEntityNode* head = nullptr;
  CEntityNode* last = nullptr;

 public:
  int highest_ent;  // Index of the last entity
  int ent_count;    // Count of existing entities

 public:
  void Insert(IBaseEntity* ent);
  void RemoveByIndex(int idx);

  IBaseEntity* GetByIndex(int idx);

  IBaseEntity* GetByPos(const SDL_Rect& pos);

  CEntityNode* GetHead();

  ~CEntityList();
};

extern CEntityList entity_list;