cmake_minimum_required(VERSION 3.23)
project(Chess)

set(CMAKE_CXX_STANDARD 20)

include_directories(dependencies/Irrklang/include)
link_directories(dependencies/Irrklang/bin/linux-gcc-64/)

add_subdirectory("dependencies/glad")
add_subdirectory("dependencies/glfw")

add_executable(Chess main.cpp Shader.cpp Shader.h Board.cpp Board.h Textures.cpp Textures.h Renderer.cpp Renderer.h Moves.cpp Moves.h Sounds.cpp Sounds.h)

target_link_libraries(Chess PUBLIC glfw glad IrrKlang)