cmake_minimum_required(VERSION 3.27)
project(tp_course_spring24_project CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(tp_course_spring24_project
        include/entity.h
        include/equipment.h
        include/room.h
        src/main.cpp
        include/types.h
        include/player.h
        src/entity.cpp
        src/player.cpp)
