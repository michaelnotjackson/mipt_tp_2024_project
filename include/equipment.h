#pragma once

#include <string>
#include <utility>
#include <types.h>

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

class RangedWeapon: BaseWeapon {
 private:
  int range;
  std::string ammo_type;
  //not string, but enum Ammo

 public:
  RangedWeapon();
};

class BaseArmor: BaseEquipment {
 private:
  int minimum_strength;
  std::pair<CharacteristicType, int> modifier;
  int armor_points;

 public:
  BaseArmor();
};

class Potion: BaseEquipment {
 private:
  int hp;
  std::string true_name;

 public:
  Potion();
};