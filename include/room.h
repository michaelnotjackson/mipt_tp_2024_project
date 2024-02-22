#pragma once

#include <vector>

class Room {
 private:
  int width;
  int height;
  std::vector<std::vector<BaseEntity>> field(height, std::vector<BaseEntity>(width));
};