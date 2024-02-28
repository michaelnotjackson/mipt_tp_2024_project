#pragma once

#include <entity.h>

#include <string>

class CEntityNode {
 public:
  IBaseEntity* entity = nullptr;
  CEntityNode* next = nullptr;
  CEntityNode* prev = nullptr;
  int idx;
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

  CEntityNode* GetHead();

  int EntityCount();
};

extern CEntityList entity_list;