#pragma once

#include <entity.h>
#include <equipment.h>
#include <types.h>

class CBasePlayer : public IBaseEntity {
 public:
  explicit CBasePlayer(CBaseAnimation& animation) : IBaseEntity(animation) {}
  std::vector<CSpell*> spell_list;
  std::vector<CBaseEquipment*> inventory;
};

class CBaseMonster : public IBaseEntity {
 public:
  std::vector<CBaseEquipment*> loot;
};