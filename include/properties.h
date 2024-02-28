#pragma once

#include <map>
#include <string>

enum class PropValueType { INT, STRING };

struct CProp {
  PropValueType value_type;
  void* value;
};

class CObjProperties {
 private:
  std::map<std::string, CProp> props;

 public:
  CProp* GetProp(const std::string& name);
};