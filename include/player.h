#pragma once

#include <entity.h>
#include <equipment.h>
#include <types.h>

class CBasePlayer : IBaseEntity {
 public:
  std::vector<CSpell*> spell_list;
  std::vector<CBaseEquipment*> inventory;
};

class CBaseMonster : IBaseEntity {
 public:
  std::vector<CBaseEquipment*> loot;
};