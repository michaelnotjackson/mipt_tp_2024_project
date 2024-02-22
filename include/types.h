#pragma once

#include <utility>
class SpriteType {};

enum SizeType {
  TINY,
  SMALL,
  MEDIUM,
  LARGE,
  HUGE
};

enum ObstacleType {
  NO_OBSTACLES,
  HALF_SPEED,
  WALL
};

enum CharacteristicType {
  STR,
  DEX,
  CON,
  INT,
  WIS,
  CHR
};

enum RaceType {

};

enum ClassType {

};

enum EntityState {

};

typedef std::pair<int, int> PosType;