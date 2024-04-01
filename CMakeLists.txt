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

add_library(engine
    src/engine/entity.cpp
    src/engine/room.cpp
    src/engine/equipment.cpp
    src/engine/renderer.cpp
    src/engine/animation.cpp
    src/engine/entitylist.cpp
    src/engine/assets_storage.cpp
    src/engine/globals.cpp
    src/engine/event_storage.cpp
    src/engine/mouse_eventlisteners.cpp
    src/engine/utils.cpp
    src/engine/turn_controller.cpp
    src/engine/player.cpp
    src/engine/playable_classes.cpp
    src/engine/playable_races.cpp
    src/engine/dice_roller.cpp
    src/engine/engine_init.cpp
)

add_executable(client
    src/main.cpp
    src/CApp.cpp

)

target_link_libraries(engine PUBLIC SDL2)
target_link_libraries(engine PUBLIC SDL2_image)
target_link_libraries(client PRIVATE engine)
