cmake_minimum_required(VERSION 3.6)
project(suberMario)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)


set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES
        suberMario.cpp LTexture.cpp LTexture.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

if (NOT SDL2_FOUND)
    message(ERROR " SDL2 not found!")
endif (NOT SDL2_FOUND)

INCLUDE(FindPkgConfig)

add_executable(suberMario ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(suberMario ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})