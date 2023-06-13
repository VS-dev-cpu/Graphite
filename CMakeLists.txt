cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Source Files
set(SOURCES
    src/Engine.cpp

    src/MediaEngine.cpp
    src/PhysicsEngine.cpp
    src/ResourceManager.cpp

    src/Renderer.cpp

    src/log.cpp

    src/GL/glad.c
)

# Libraries
set(LIBRARIES
    pthread
    glfw
    #ReactPhysics3D::ReactPhysics3D
)

project(Graphite VERSION 0.1.0 LANGUAGES C CXX)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Examples
add_subdirectory(hello_graphite)
