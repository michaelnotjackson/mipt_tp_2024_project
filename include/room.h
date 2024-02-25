#pragma once

#include <vector>
#include <types.h>
#include <entity.h>

class CTile {
 private:
  SDL_Texture* texture;
  TileFlagsType flags;

 public:
  void SetTexture(SDL_Texture* texture);
  void SetFlags(TileFlagsType flags);
};

class Room {
 private:
  int width;
  int height;
  FieldType field;

 public:
  Room(int width,
       int height,
       FieldType field);

  int GetWidth();
  int GetHeight();
  FieldType& GetField();
};