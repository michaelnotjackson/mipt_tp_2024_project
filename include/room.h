#pragma once

#include <entity.h>
#include <types.h>

#include <vector>

class CTile {
 private:
  CBaseAnimation animation;
  TileFlagsType flags;

 public:
  void SetTexture(CBaseAnimation texture);
  void SetFlags(TileFlagsType flags);

  CBaseAnimation GetTexture();

  CTile(CBaseAnimation texture);

  CTile();
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

  FieldType& GetField();
  void SetField (SDL_Texture* texture);
  void DrawField ();
};

PosType GetTilePos(const CTile& tile, const Room& room);