cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Source Files
set(SOURCES
    src/Engine.cpp

    # Core
    src/MediaEngine.cpp
    src/ResourceManager.cpp

    src/log.cpp

    # Graphics

    # - OpenGL
    src/graphics/OpenGL/OpenGL.cpp
    src/graphics/OpenGL/glad.c

    # - Vulkan
    src/graphics/Vulkan/Vulkan.cpp

)

# Libraries
set(LIBRARIES
    pthread
    glfw
)

# Project (Library)
project(Graphite VERSION 0.1.0 LANGUAGES C CXX)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC "include")

# Examples
add_subdirectory(hello_graphite)
