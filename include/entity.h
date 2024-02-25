#pragma once

#include <SDL.h>
#include <types.h>

#include <string>
#include <utility>
#include <vector>

class CBaseEntity {
 private:
  int hp;
  PosType pos;
  SizeType size;
  SDL_Texture* texture;
  ObstacleType obstacle_degree;

 public:
  CBaseEntity();

  int GetHp();
  void SetHp(int new_hp);

  PosType GetPos();
};

class Combatable {
 private:
  int armor_points;
  int mastery_bonus;
  int characteristics[6] = {0};

 public:
  virtual void Hit() = 0;
  virtual void Cast() = 0;
};

class Movable {
 private:
  int speed;
  int state;

 public:
  virtual void MoveTo(PosType new_pos) = 0;
};