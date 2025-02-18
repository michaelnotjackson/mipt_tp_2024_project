#pragma once

#include <utility>
#include <vector>

#ifdef HUGE
#undef HUGE
#endif

enum class SizeType { TINY, SMALL, MEDIUM, LARGE, HUGE };

enum class ObstacleType {
  NO_OBSTACLES = 5,
  HALF_SPEED = 10,
  WALL = static_cast<int>(1e9),
  DOOR = 4
};

enum class CharacteristicType { STR, DEX, CON, INT, WIS, CHR };

enum class RaceType {
  human
};

enum class ClassType {
  fighter
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

class CTile;

typedef std::vector<std::vector<CTile*>> FieldType;

struct PosType {
  int x;
  int y;

  PosType(): x(0), y(0) {}
  PosType(int x, int y) : x(x), y(y) {}

  bool operator==(const PosType& oth) const { return x == oth.x && y == oth.y; };
  bool operator!=(const PosType& oth) const { return !(*this == oth); };
};

class CSpell {};