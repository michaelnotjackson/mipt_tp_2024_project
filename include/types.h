#pragma once

#include <utility>
#include <vector>

#ifdef HUGE
#undef HUGE
#endif

enum class SizeType { TINY, SMALL, MEDIUM, LARGE, HUGE };

enum class ObstacleType { NO_OBSTACLES, HALF_SPEED, WALL };

enum class CharacteristicType { STR, DEX, CON, INT, WIS, CHR };

enum class RaceType {

};

enum class ClassType {

};

enum class EntityState {

};

enum class WeaponProperties {
  FINESSE = 1 << 0,
  HEAVY = 1 << 1,
  LIGHT = 1 << 2,
  LOADING = 1 << 3,
  REACH = 1 << 4,
  RANGE = 1 << 5,
  SPECIAL = 1 << 6,
  TWO_HANDED = 1 << 7,
  VERSATILE = 1 << 8
};

enum class EquipType { BASEWEAPON, RANGEWEAPON, BASEARMOR, POTION };

enum class DamageType {
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
  PSYCHIC
};

enum class TileFlagsType { VISIBLE = 1 << 0 };

class CTile;

typedef std::vector<std::vector<CTile*>> FieldType;

struct PosType {
  int x;
  int y;

  PosType(): x(0), y(0) {}
  PosType(int x, int y) : x(x), y(y) {}

  bool operator==(const PosType& oth) const = default;
  bool operator!=(const PosType& oth) const = default;
};

class CSpell {};