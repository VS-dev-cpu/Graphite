#pragma once

#include <GameEngine/core/log.h>

#include <GameEngine/types/base.h>

namespace GameEngine
{
    namespace LOAD
    {
        // Text / String
        std::string Text(std::string path, std::string ext = "");

        // Load Image
        texture Image(std::string path);

        // Load Shader
        shader Shader(std::string vertex_path, std::string fragment_path, std::string geometry_path = "");

        // Load Mesh
        mesh Mesh(std::string path);
    }
}