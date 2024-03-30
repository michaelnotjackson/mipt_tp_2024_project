cmake_minimum_required(VERSION 3.26)
project(tp_course_spring24_project CXX)

set(PROJECT_NAME DND_RogueLike)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

include_directories(.)
include_directories(include)
include_directories(src)

add_subdirectory(include/SDL)
add_subdirectory(include/SDL_image)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY rooms DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include/SDL_image/include)
include_directories(include/SDL/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/entity.cpp
    src/room.cpp
    src/equipment.cpp
    src/interface/CApp.cpp
    src/interface/renderer.cpp
    src/animation.cpp
    src/entitylist.cpp
    src/assets_storage.cpp
    src/globals.cpp
    src/event_storage.cpp
    src/mouse_eventlisteners.cpp
    src/utils.cpp
    src/turn_controller.cpp
    src/player.cpp
    src/playable_classes.cpp
    src/playable_races.cpp
    src/dice_roller.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE SDL2)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE SDL2_image)
