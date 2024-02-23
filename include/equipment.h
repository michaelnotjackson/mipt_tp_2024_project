#pragma once

#include <types.h>

#include <string>
#include <utility>

class BaseEquipment {
 private:
  std::string name;
  EquipType type;
  int cost;
  double weight;
  int count;

 public:
  BaseEquipment(std::string name, EquipType type, int cost, double weight,
                int count);

  std::string GetName();
  EquipType GetEquipType();
  int GetCost();
  double GetWeight();
  int GetCount();

  void ChangeCount(int count);
};

class BaseWeapon : BaseEquipment {
 private:
  int damage;
  Properties properties;
  DamageType type;

 public:
  BaseWeapon(std::string name, EquipType equip_type, int cost, double weight,
             int count, int damage, Properties properties,
             DamageType damage_type);

  Properties GetProperties();
  DamageType GetDamageType();
};

class RangedWeapon : BaseWeapon {
 private:
  int range;
  std::string ammo_type;
  // not string, but enum Ammo

 public:
  RangedWeapon(int damage, Properties properties, DamageType type, int range,
               std::string ammo_type);

  int GetRange();
  std::string GetAmmoType();
};

class BaseArmor : BaseEquipment {
 private:
  int minimum_strength;
  std::pair<CharacteristicType, int> modifier;
  int armor_points;

 public:
  BaseArmor(std::string name, EquipType type, int cost, double weight,
            int count, int minimum_strength,
            std::pair<CharacteristicType, int> modifier, int armor_points);

  int GetMinStrength();
  std::pair<CharacteristicType, int> GetModifier();
  int GetArmorPoints();
};

class Potion : BaseEquipment {
 private:
  int hp;
  std::string true_name;

 public:
  Potion(int hp, std::string true_name);

  int GetHP();
  std::string GetTrueName();
  void ChangeTrueName(std::string true_name);
};