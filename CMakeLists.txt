cmake_minimum_required(VERSION 3.23)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(../glfw/include)
include_directories(include)

link_libraries(GL glfw3 -l:libGLEW.a)


link_directories(include/GL)
link_directories(../glfw/build/src/)

add_executable(Chess main.cpp Game.cpp Game.h Item.h stb_image.cpp stb_image.h Board.cpp Board.h Texture.cpp Texture.h)
