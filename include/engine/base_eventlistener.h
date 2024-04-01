#pragma once

class IBaseEventListener {
 public:
  virtual void notify() = 0;
  virtual void reset() = 0;
};