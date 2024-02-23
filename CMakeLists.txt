cmake_minimum_required(VERSION 3.26)
project(tp_course_spring24_project CXX)

set(PROJECT_NAME DND_RougeLike)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

option(SYSTEM_SDL "Use SDL installed in your system" OFF)

if (SYSTEM_SDL)
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
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
        src/player.cpp
        include/interface/shared_vars.h
        include/interface/init.h
        include/interface/input.h
        src/interface/init.cpp
        src/interface/input.cpp
        include/interface/draw.h
        src/interface/draw.cpp
        include/interface/interface.h)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)