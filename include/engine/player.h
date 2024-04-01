#pragma once

#include "entity.h"
#include "equipment.h"
#include "types.h"

class CBasePlayer : public IBaseEntity {
 public:
  explicit CBasePlayer(CBaseAnimation& animation,
                       ClassType player_class = ClassType::fighter,
                       RaceType player_race = RaceType::human,
                       const std::string& name = "Player", int team = 1);

  std::vector<CSpell*> spell_list;
  std::vector<CBaseEquipment*> inventory;
};

class CBaseMonster : public IBaseEntity {
 public:
  std::vector<CBaseEquipment*> loot;
};