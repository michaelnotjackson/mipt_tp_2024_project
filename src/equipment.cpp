#include <equipment.h>

#include <utility>

std::string CBaseEquipment::GetName() { return this->name; }
EquipType CBaseEquipment::GetEquipType() { return this->type; }
int CBaseEquipment::GetCost() { return this->cost; }
double CBaseEquipment::GetWeight() { return this->weight; }
int CBaseEquipment::GetCount() { return this->count; }

void CBaseEquipment::ChangeCount(int count) { this->count = count; }

CBaseEquipment::CBaseEquipment(std::string name, EquipType type, int cost,
                             double weight, int count)
    : name(name), type(type), cost(cost), weight(weight), count(count){};

WeaponProperties CBaseWeapon::GetProperties() { return this->properties; }
DamageType CBaseWeapon::GetDamageType() { return this->type; }

CBaseWeapon::CBaseWeapon(std::string name, EquipType equip_type, int cost,
                       double weight, int count, int damage,
                         WeaponProperties properties, DamageType damage_type)
    : CBaseEquipment(name, equip_type, cost, weight, count),
      damage(damage),
      properties(properties),
      type(damage_type){};

int CRangedWeapon::GetRange() { return this->range; }
std::string CRangedWeapon::GetAmmoType() { return this->ammo_type; }

CRangedWeapon::CRangedWeapon(int damage, WeaponProperties properties, DamageType type,
                           int range, std::string ammo_type)
    : CBaseWeapon(std::string(), BASEARMOR, 0, 0, 0, damage, properties, type),
      range(range),
      ammo_type(ammo_type){};

int CBaseArmor::GetMinStrength() { return this->minimum_strength; }
std::pair<CharacteristicType, int> CBaseArmor::GetModifier() {
  return this->modifier;
}
int CBaseArmor::GetArmorPoints() { return this->armor_points; }

CBaseArmor::CBaseArmor(std::string name, EquipType type, int cost, double weight,
                     int count, int minimum_strength,
                     std::pair<CharacteristicType, int> modifier,
                     int armor_points)
    : CBaseEquipment(name, type, cost, weight, count),
      minimum_strength(minimum_strength),
      modifier(modifier),
      armor_points(armor_points){};

int CBasePotion::GetHP() { return this->hp; }
std::string CBasePotion::GetTrueName() { return this->true_name; }
void CBasePotion::ChangeTrueName(std::string true_name) { true_name = true_name; }