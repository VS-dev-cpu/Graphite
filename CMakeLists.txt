cmake_minimum_required(VERSION 3.8)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -Wall")

set(CMAKE_PREFIX_PATH "/usr/lib;/usr/local/lib")

find_package(ReactPhysics3D REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(include)

project(GameEngine)

add_library(GameEngine
    # -- Main --
    src/GameEngine.cpp

    # -- Core --

    src/core/load.cpp
    
    # / tools
    src/core/tools/log.cpp

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

target_link_libraries(GameEngine ReactPhysics3D::ReactPhysics3D)
target_link_libraries(GameEngine glfw)

add_subdirectory(hello_world)
