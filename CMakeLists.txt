cmake_minimum_required(VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(glfw3 REQUIRED)
find_package(ReactPhysics3D REQUIRED)

include_directories("include")

link_libraries(glfw ReactPhysics3D::ReactPhysics3D)

# Graphite (Game Engine) Project
project(Graphite)

add_library(Graphite
    src/Engine.cpp

    src/MediaEngine.cpp
    src/PhysicsEngine.cpp
    src/ResourceManager.cpp

    src/Renderer.cpp

    src/log.cpp

    src/GL/glad.c
    src/stb_image.c
)

# Hello World Example
add_subdirectory(hello_graphite)
