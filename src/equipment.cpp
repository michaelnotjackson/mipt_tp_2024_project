#include <equipment.h>

#include <utility>

std::string BaseEquipment::GetName() { return this->name; }
EquipType BaseEquipment::GetEquipType() { return this->type; }
int BaseEquipment::GetCost() { return this->cost; }
double BaseEquipment::GetWeight() { return this->weight; }
int BaseEquipment::GetCount() { return this->count; }

void BaseEquipment::ChangeCount(int count) { this->count = count; }

BaseEquipment::BaseEquipment(std::string name, EquipType type, int cost,
                             double weight, int count)
    : name(name), type(type), cost(cost), weight(weight), count(count){};

Properties BaseWeapon::GetProperties() { return this->properties; }
DamageType BaseWeapon::GetDamageType() { return this->type; }

BaseWeapon::BaseWeapon(std::string name, EquipType equip_type, int cost,
                       double weight, int count, int damage,
                       Properties properties, DamageType damage_type)
    : BaseEquipment(name, equip_type, cost, weight, count),
      damage(damage),
      properties(properties),
      type(damage_type){};

int RangedWeapon::GetRange() { return this->range; }
std::string RangedWeapon::GetAmmoType() { return this->ammo_type; }

RangedWeapon::RangedWeapon(int damage, Properties properties, DamageType type,
                           int range, std::string ammo_type)
    : BaseWeapon(std::string(), BASEARMOR, 0, 0, 0, damage, properties, type),
      range(range),
      ammo_type(ammo_type){};

int BaseArmor::GetMinStrength() { return this->minimum_strength; }
std::pair<CharacteristicType, int> BaseArmor::GetModifier() {
  return this->modifier;
}
int BaseArmor::GetArmorPoints() { return this->armor_points; }

BaseArmor::BaseArmor(std::string name, EquipType type, int cost, double weight,
                     int count, int minimum_strength,
                     std::pair<CharacteristicType, int> modifier,
                     int armor_points)
    : BaseEquipment(name, type, cost, weight, count),
      minimum_strength(minimum_strength),
      modifier(modifier),
      armor_points(armor_points){};

int Potion::GetHP() { return this->hp; }
std::string Potion::GetTrueName() { return this->true_name; }
void Potion::ChangeTrueName(std::string true_name) { true_name = true_name; }