cmake_minimum_required(VERSION 3.8)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -Wall")

#set(CMAKE_PREFIX_PATH "/usr/lib;/usr/local/lib")

find_package(ReactPhysics3D REQUIRED)
add_subdirectory(Artifex)

include_directories("include" "Artifex/include")
link_libraries(Artifex ReactPhysics3D::ReactPhysics3D)

project(GameEngine)

add_library(GameEngine
    src/GameEngine.cpp

    src/MediaEngine.cpp
    src/PhysicsEngine.cpp

    src/load.cpp
    src/log.cpp
)

add_subdirectory(hello_graphite)
