cmake_minimum_required(VERSION 3.23)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("dependencies/glad")
add_subdirectory("dependencies/glfw")

add_executable(Chess main.cpp Shader.cpp Shader.h)

target_link_libraries(Chess PUBLIC glfw glad)