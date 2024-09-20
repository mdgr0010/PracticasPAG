cmake_minimum_required(VERSION 3.29)
project(PR1)

find_package(glad)
find_package(glfw3)
find_package(glew)

set(CMAKE_CXX_STANDARD 20)

add_executable(PR1 main.cpp
        Renderer.cpp
        Renderer.h)

target_link_libraries(PR1 glad::glad)
target_link_libraries(PR1 glfw)
target_link_libraries(PR1 GLEW::GLEW)