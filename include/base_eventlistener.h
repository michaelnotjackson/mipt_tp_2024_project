#pragma once

class IBaseEventListener {
 public:
  virtual void notify() = 0;
};