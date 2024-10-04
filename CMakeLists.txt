cmake_minimum_required(VERSION 3.29)
project(PracticasPAG)

find_package(glad)
find_package(glfw3)

set(CMAKE_CXX_STANDARD 20)

file ( GLOB IMGUI imgui/*.cpp )

add_executable(${PROJECT_NAME} main.cpp
        Renderer.cpp
        Renderer.h
        ${IMGUI}
        GUI.cpp
        GUI.h
        ShaderProgram.cpp
        ShaderProgram.h
        Shader.cpp
        Shader.h)

target_link_libraries(${PROJECT_NAME} glad::glad)
target_link_libraries(${PROJECT_NAME} glfw)