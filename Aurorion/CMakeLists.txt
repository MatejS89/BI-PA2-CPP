cmake_minimum_required(VERSION 3.25)
project(Aurorion)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/Users/brami/Dev/C++/sedlam53/Aurorion/src/include)
set(SDL2_LIB_DIR C:/Users/brami/Dev/C++/sedlam53/Aurorion/src/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(Aurorion main.cpp game.h game.cpp game.cpp game.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
