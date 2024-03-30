#include <playable_classes.h>

#include <map>

std::map<ClassType, CObjProperties> playable_classes(
    {{ClassType::fighter,
      {
          {"d_health_dice", 10},
          {"i_base_health", 10},
          {"c_health_lvl_modifier",
           CharacteristicType::CON},
          {"i_health_lvl_modifier", 6},
          {"v_proficiency_savethrows",
           std::vector<CharacteristicType>({CharacteristicType::STR,
                                            CharacteristicType::CON})},
      }}});