#pragma once

#include <vector>
#include <types.h>
#include <entity.h>

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