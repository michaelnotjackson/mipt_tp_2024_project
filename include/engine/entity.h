#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "animation.h"
#include "include/SDL/include/SDL.h"
#include "properties.h"
#include "types.h"

class IBaseEntity {
 protected:
  PosType pos; // Position on the map!
  CBaseAnimation default_animation;

 public:
  CBaseAnimation animation;
  CObjProperties props;
  int characteristics[6];

 public:
  virtual CObjProperties* GetProperties();

  virtual PosType* GetPos();
  virtual void MoveBy(std::vector<PosType>* path);

  virtual void SetAnimation(const CBaseAnimation& new_animation);
  virtual void SetAnimation();
  virtual void PlayAnimation(const CBaseAnimation& new_animation);


 public:
  explicit IBaseEntity(CBaseAnimation& animation);

  virtual ~IBaseEntity() = default;
};