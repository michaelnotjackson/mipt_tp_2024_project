#pragma once

#include <string>
#include <utility>

#include "include/SDL/include/SDL.h"
#include "types.h"

class CBaseEquipment {
 private:
  std::string name;
  EquipType type;
  SDL_Texture* texture;

  int cost;
  double weight;
  int count;

 public:
  CBaseEquipment(const std::string& name, const EquipType& type, int cost, double weight,
                 int count);

  std::string GetName();
  EquipType GetEquipType();
  int GetCost();
  double GetWeight();
  int GetCount();

  void ChangeCount(int count);
};

class CBaseWeapon : CBaseEquipment {
 private:
  int damage;
  WeaponProperties properties;
  DamageType type;

 public:
  CBaseWeapon(const std::string& name, const EquipType& equip_type, int cost, double weight,
              int count, int damage, const WeaponProperties& properties,
              const DamageType& damage_type);

  WeaponProperties GetProperties();
  DamageType GetDamageType();
};

class CRangedWeapon : CBaseWeapon {
 private:
  int range;
  std::string ammo_type;

 public:
  CRangedWeapon(int damage, const WeaponProperties& properties, const DamageType& type,
                int range, const std::string& ammo_type);

  int GetRange();
  std::string GetAmmoType();
};

class CBaseArmor : CBaseEquipment {
 private:
  int minimum_strength;
  std::pair<CharacteristicType, int> modifier;
  int armor_points;

 public:
  CBaseArmor(const std::string& name, const EquipType& type, int cost, double weight,
             int count, int minimum_strength,
             const std::pair<CharacteristicType, int>& modifier, int armor_points);

  int GetMinStrength();
  std::pair<CharacteristicType, int> GetModifier();
  int GetArmorPoints();
};

class CBasePotion : CBaseEquipment {
 private:
  int hp;
  std::string true_name;

 public:
  CBasePotion(int hp, std::string true_name);

  int GetHP();
  std::string GetTrueName();
  void ChangeTrueName(const std::string& true_name);
};