cmake_minimum_required(VERSION 3.27)
project(tp_course_spring24_project CXX)

set(PROJECT_NAME DND_RougeLike)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

option(SYSTEM_SDL "Use SDL installed in your system" ON)

if (SYSTEM_SDL)
  find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
else ()
  add_subdirectory(include/SDL EXCLUDE_FROM_ALL)
endif ()

add_executable(${PROJECT_NAME}
    include/entity.h
    include/equipment.h
    include/room.h
    src/main.cpp
    include/types.h
    include/player.h
    src/entity.cpp
    src/player.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)