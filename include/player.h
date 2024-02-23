#pragma once

#include <entity.h>
#include <equipment.h>
#include <types.h>

class Player : public BaseEntity, public Movable, public Combatable {
 private:
  Player(RaceType race, ClassType ply_class, int spell_list, int inventory,
         std::string name, int team_id);
  RaceType race;
  ClassType ply_class;
  int mp;
  std::vector<SpellType> spell_list;
  std::vector<BaseEquipment*> inventory;
  double max_carry_weight;
  int lvl;
  int xp;
  std::string name;
  int team_id;

 public:
  Player(RaceType race, ClassType ply_class, std::vector<SpellType> spell_list,
         std::vector<BaseEquipment*> inventory, std::string name, int team_id);

  RaceType GetRace();
  ClassType GetClass();

  int GetMana();
  void SetMana(int mana);

  double GetMaxCarryWeight();
  void SetMaxCarryWeight(double weight);

  int GetLvl();
  void SetLvl(int lvl);

  int GetXp();
  void SetXp(int xp);

  std::string GetName();
  void ChangeName(std::string name);

  int GetTeam();
  void SetTeam(int team_id);
};

class Monster : public BaseEntity, public Movable, public Combatable {
  std::string type;
  int xp;
  int team_id;
  std::vector<BaseEquipment*> loot;
};