#pragma once

#include <entity.h>
#include <types.h>

#include <vector>

class CTile {
 private:
  CBaseAnimation animation;
  ObstacleType flag;

 public:
  void SetTexture(CBaseAnimation texture);
  void SetFlags(ObstacleType flag);
  ObstacleType GetFlag();

  CBaseAnimation GetTexture() const;

  CTile(CBaseAnimation texture, ObstacleType flag);

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

  Room(int width,
       int height);

  Room() = default;

 public:
  int GetWidth();
  int GetHeight();
  const FieldType& GetField() const;
  void SetField (SDL_Texture* texture);
  void DrawField ();
};

PosType GetTilePos(const CTile* tile, const Room& room);