#include <entity.h>

CObjProperties* IBaseEntity::GetProperties() {
  return &this->props;
}

PosType* IBaseEntity::GetPos() {
  return &this->pos;
}