cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1 -Wall")

find_package(ReactPhysics3D REQUIRED)

project(GameEngine)

add_library(GameEngine
    # -- Main --
    src/GameEngine.cpp

    # -- Core --
    src/core/log.cpp
    src/core/load.cpp

    # / MediaEngine
    src/core/MediaEngine/MediaEngine.cpp

    # > / windowers
    src/core/MediaEngine/windowers/glfw.cpp

    # > / renderers
    src/core/MediaEngine/renderers/OpenGL.cpp
    
    # / PhysicsEngine
    src/core/PhysicsEngine/PhysicsEngine.cpp

    # -- Utility --
    src/utility/glad.c
    src/utility/stb_image.c
    )

target_include_directories(GameEngine PUBLIC include)

target_link_libraries(GameEngine ReactPhysics3D::ReactPhysics3D)
target_link_libraries(GameEngine glfw)

add_subdirectory(hello_world)
