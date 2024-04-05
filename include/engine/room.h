#pragma once

#include <set>
#include <vector>

#include "entity.h"
#include "types.h"

class CTile {
 private:
  CBaseAnimation animation;
  ObstacleType obstacle_type;

 public:
  IBaseEntity* entity_on;

 public:
  void SetTexture(CBaseAnimation texture);

  void SetObstacleType(ObstacleType obstacle_type);

  ObstacleType GetObstacleType();

  CBaseAnimation GetTexture() const;

  CTile(CBaseAnimation texture, ObstacleType obstacleType);

  CTile();

  bool operator==(const CTile& pic_1) const = default;
};

class Room {
 private:
  int width;
  int height;

 public:
  FieldType field;

 public:
  Room(int width, int height, FieldType field);

  Room(int width, int height);

  Room() = default;

 public:
  int GetWidth();

  int GetHeight();

  const FieldType& GetField() const;

  void SetField();

  void DrawField();
};

PosType GetTilePos(const CTile* tile, const Room& room);