#pragma once

#include "types.h"

#include <utility>
#include <vector>
#include <string>

class BaseEntity {
 private:
  int hp;
  PosType pos;
  SizeType size;
  SpriteType sprite;
  ObstacleType obstacle_degree;

 public:
  BaseEntity();

  int GetHp();
  void ChangeHp(int new_hp);

  std::pair<int, int> GetPos();
};

class Combatable {
 private:
  int armor_points;
  int mastery_bonus;
  int characteristics[6] = {0};

 public:
  virtual void Hit() = 0;
  virtual void Cast() = 0;

  Combatable() = delete;
};

class Movable {
 private:
  int speed;
  int state;

 public:
  virtual void MoveTo(PosType new_pos) = 0;

  Movable() = delete;
};