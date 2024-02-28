#pragma once

#include <SDL.h>
#include <animation.h>
#include <properties.h>
#include <types.h>

#include <map>
#include <memory>
#include <string>
#include <utility>

class IBaseEntity {
 private:
  CObjProperties props;
  PosType pos;

 public:
  CBaseAnimation animation;

 public:
  virtual CObjProperties* GetProperties();
  virtual PosType* GetPos();

  virtual ~IBaseEntity() = default;

 public:
  IBaseEntity(const CBaseAnimation& animation);
};