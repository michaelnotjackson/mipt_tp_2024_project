#pragma once

#include <string>
#include <utility>

enum Properties {
  FINESSE = 1 << 0,
  HEAVY = 1 << 1,
  LIGHT = 1 << 2,
  LOADING = 1 << 3,
  REACH = 1 << 4,
  RANGE = 1 << 5,
  SPECIAL = 1 << 6,
  TWO_HANDED = 1 << 7,
  VERSATILE = 1 << 8;
};

enum Equip {
  BASEWEAPON,
  RANGEWEAPON,
  BASEARMOR,
  POTION;
};

enum Damage {
  SLASHING,
  PIERCING,
  BLUDGEONING,
  POISON,
  ACID,
  FIRE,
  COLD,
  RADIANT,
  NECROTIC,
  LIGHTNING,
  THUNDER,
  FORCE,
  PSYCHIC;
};

class BaseEquipment {
 private:
  std::string name;
  Equip type;
  int cost;
  double weight;
  int count;

 public:
  BaseEquipment();
};

class BaseWeapon: BaseEquipment {
 private:
  int damage;
  Properties properties;
  Damage type;

 public:
  BaseWeapon();
};

class RangedWeapon {
 private:
  int range;
  std::string ammo_type;
  //not string, but enum Ammo

 public:
  RangedWeapon();
};

class BaseArmor {
 private:
  int minimum_strength;
  std::pair<CharacteristicType, int> modifier;
  int armor_points;

 public:
  BaseArmor();
};

class Potion {
 private:
  int hp;
  std::string true_name;

 public:
  Potion();
};