cmake_minimum_required(VERSION 3.29)
project(PR1)

find_package(glad)
find_package(glfw3)

set(CMAKE_CXX_STANDARD 20)

file ( GLOB IMGUI imgui/*.cpp )

add_executable(PR1 main.cpp
        Renderer.cpp
        Renderer.h
        ${IMGUI}
        GUI.cpp
        GUI.h)

target_link_libraries(PR1 glad::glad)
target_link_libraries(PR1 glfw)