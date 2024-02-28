#pragma once

#include <entity.h>
#include <types.h>

#include <vector>

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
  Arr field_0;

 public:
  Room(int width, int height, FieldType field);

  Room(int width,
       int height);

  int GetWidth();
  int GetHeight();
  FieldType& GetField();
  void SetField ();
  void DrawField (SDL_Texture* texture);
};