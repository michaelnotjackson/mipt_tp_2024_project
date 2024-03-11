cmake_minimum_required(VERSION 3.26)
project(tp_course_spring24_project CXX)

set(PROJECT_NAME DND_RougeLike)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})

include_directories(.)
include_directories(include)
include_directories(src)

add_subdirectory(include/SDL)
add_subdirectory(include/SDL_image)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

include_directories(include/SDL_image/include)
include_directories(include/SDL/include)

add_executable(${PROJECT_NAME}
        include/entity.h
        include/equipment.h
        include/room.h
        src/main.cpp
        include/types.h
        include/player.h
        src/entity.cpp
        include/interface/CApp.h
        src/room.cpp
        src/equipment.cpp
        src/interface/CApp.cpp
        include/interface/renderer.h
        src/interface/renderer.cpp
        include/animation.h
        src/animation.cpp
        include/properties.h
        include/entitylist.h
        src/entitylist.cpp
        include/assets_manager.h
        src/assets_manager.cpp
        include/globals.h
        src/globals.cpp
        include/eventmanager.h
        include/base_eventlistener.h
        include/mouse_eventlisteners.h
        src/eventmanager.cpp
        src/mouse_eventlisteners.cpp
        include/utils.h
        src/utils.cpp
    include/turnmanager.h
    src/turnmanager.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE SDL2)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE SDL2_image)
