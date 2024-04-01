#pragma once

#include <map>
#include <string>
#include <variant>

#include "types.h"

typedef std::variant<int, std::string, CharacteristicType, std::vector<CharacteristicType>, std::vector<int>> CProp;

typedef std::map<std::string, CProp> CObjProperties;

template <typename T>
T& GetPropValue(CObjProperties& properties_obj, const std::string& name) {
  return get<T>(properties_obj[name]);
}