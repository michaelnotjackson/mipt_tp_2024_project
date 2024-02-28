#include <room.h>

#include <utility>

int Room::GetWidth() { return this->width; }
int Room::GetHeight() { return this->height; }
FieldType& Room::GetField() { return this->field; }

Room::Room(int width, int height, FieldType field)
    : width(width), height(height), field(std::move(field)){};