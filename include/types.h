#pragma once

#include <utility>
class SpriteType {};

enum SizeType { TINY, SMALL, MEDIUM, LARGE, HUGE };

enum ObstacleType { NO_OBSTACLES, HALF_SPEED, WALL };

enum CharacteristicType { STR, DEX, CON, INT, WIS, CHR };

enum RaceType {

};

enum ClassType {

};

enum EntityState {

};

enum Properties {
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

enum EquipType {
  BASEWEAPON,
  RANGEWEAPON,
  BASEARMOR,
  POTION
};

enum DamageType {
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

<<<<<<< HEAD
class BaseEntity;
typedef std::vector<std::vector<BaseEntity&>> FieldType;

typedef std::pair<int, int> PosType;
=======
struct PosType {
  int x;
  int y;
};
>>>>>>> 8743bf258d95e4956ac5f4b682218df3f7948164
