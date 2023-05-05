cmake_minimum_required(VERSION 3.25)
project(Aurorion)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR C:/Users/brami/Dev/C++/sedlam53/Aurorion/src/SDL2/include)
set(SDL2_LIB_DIR C:/Users/brami/Dev/C++/sedlam53/Aurorion/src/SDL2/lib/x64)
set(SDL2_IMAGE_LIB C:/Users/brami/Dev/C++/sedlam53/Aurorion/src/SDL2_image-2.6.3/lib/x64)
set(SDL2_IMAGE_INCLUDE C:/Users/brami/Dev/C++/sedlam53/Aurorion/src/SDL2_image-2.6.3/include)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE})
link_directories(${SDL2_LIB_DIR} ${SDL2_IMAGE_LIB})

add_executable(Aurorion main.cpp game.h game.cpp game.cpp game.h texture_manager.cpp texture_manager.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image.lib)
