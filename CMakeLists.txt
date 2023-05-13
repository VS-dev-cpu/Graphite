cmake_minimum_required(VERSION 3.8)

find_package(ReactPhysics3D REQUIRED)

project(GameEngine)

add_library(GameEngine
    # -- Main --
    src/GameEngine.cpp

    # -- Core --
    src/core/log.cpp

    # Core > MediaEngine
    src/core/MediaEngine/MediaEngine.cpp
    
    # Core > PhysicsEngine
    src/core/PhysicsEngine/PhysicsEngine.cpp

    # -- Utility --
    src/utility/stb_image.cpp
    src/utility/glad.c
    )

target_include_directories(GameEngine PUBLIC include)

target_link_libraries(GameEngine ReactPhysics3D::ReactPhysics3D)
target_link_libraries(GameEngine glfw)

add_subdirectory(hello_world)
