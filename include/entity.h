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
  CBaseAnimation default_animation;

 public:
  CBaseAnimation animation;

 public:
  virtual CObjProperties* GetProperties();
  virtual PosType* GetPos();

  virtual ~IBaseEntity() = default;

  virtual void SetAnimation(const CBaseAnimation& new_animation);
  virtual void SetAnimation();
  virtual void PlayAnimation(const CBaseAnimation& new_animation);

 public:
  explicit IBaseEntity(CBaseAnimation& animation)
      : default_animation(animation), animation(animation) {}
};