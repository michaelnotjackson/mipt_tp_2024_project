#include <playable_classes.h>

#include <map>
#include <string>

std::map<ClassType, CObjProperties> playable_classes(
    {{ClassType::fighter,
      {
          {"d_health_dice", {PropValueType::INT, new int(10)}},
          {"i_base_health", {PropValueType::INT, new int(10)}},
          {"c_health_lvl_modifier",
           {PropValueType::CHARACTERISTIC,
            new CharacteristicType(CharacteristicType::CON)}},
          {"i_health_lvl_modifier", {PropValueType::INT, new int(6)}},
          {"v_proficiency_savethrows",
           {PropValueType::VECTOR_CHARACTERISTIC,
            new std::vector<CharacteristicType>({CharacteristicType::STR,
                                                 CharacteristicType::CON})}},
      }}});