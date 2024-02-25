cmake_minimum_required(VERSION 3.26)
project(tp_course_spring24_project CXX)

set(PROJECT_NAME DND_RougeLike)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} include/SDL_image/cmake/FindSDL2_image.cmake)
set(SDL2_image_DIR include/SDL_image)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} include/SDL_image/include)

add_executable(${PROJECT_NAME}
        include/entity.h
        include/equipment.h
        include/room.h
        src/main.cpp
        include/types.h
        include/player.h
        src/entity.cpp
        src/player.cpp
        include/interface/CApp.h
        src/room.cpp
        src/equipment.cpp
        src/interface/CApp.cpp
    include/interface/renderer.h
    src/interface/renderer.cpp)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})