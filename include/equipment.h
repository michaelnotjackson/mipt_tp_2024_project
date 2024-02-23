#pragma once

#include <string>
#include <utility>
#include <types.h>

class BaseEquipment {
 private:
  std::string name;
  EquipType type;
  int cost;
  double weight;
  int count;

 public:
  BaseEquipment(std::string name,
                Equip type,
                int cost,
                double weight,
                int count);

  std::string GetName();

  EquipType GetEquipType();

  int GetCost();

  double GetWeight();

  int GetCount();
  void ChangeCount(int count);
};

class BaseWeapon: BaseEquipment {
 private:
  int damage;
  Properties properties;
  DamageType type;

 public:
  BaseWeapon();

  Properties GetProperties();

  DamageType GetDamageType();
};

class RangedWeapon: BaseWeapon {
 private:
  int range;
  std::string ammo_type;
  //not string, but enum Ammo

 public:
  RangedWeapon();

  int GetRange();

  std::string GetAmmoType();
};

class BaseArmor: BaseEquipment {
 private:
  int minimum_strength;
  std::pair<CharacteristicType, int> modifier;
  int armor_points;

 public:
  BaseArmor();

  int GetMinStrength();

  std::pair<CharacteristicType, int> GetModifier();

  int GetArmorPoints;
};

class Potion: BaseEquipment {
 private:
  int hp;
  std::string true_name;

 public:
  Potion();

  int GetHP();

  std::string GetTrueName();
  void ChangeTrueName(std::string);
};