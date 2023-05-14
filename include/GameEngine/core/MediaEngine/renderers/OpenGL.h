#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/utility/glad.h>

#include <GameEngine/core/MediaEngine/renderers/Renderer.h>

// windowers
#include <GameEngine/core/MediaEngine/windowers/glfw.h>

// TODO: Make it Work

namespace GameEngine::MEDIA::RENDERER
{
    class OpenGL : public Renderer
    {
    public:
        OpenGL(std::string name = "RENDERER::OpenGL", bool fullscreen = true, int width = 720, int height = 480);
        ~OpenGL();

        bool update();
        void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, uint buffers = 0x00);

        std::string add(std::string name, shader s);
        std::string add(std::string name, texture tex);

    private:
        WINDOWER::GLFW *windower = nullptr;

        // 2D Rendering
        uint VAO, VBO, EBO;

        // Shaders
        std::map<std::string, std::pair<shader, uint>> shaders;

        // Textures
        std::map<std::string, std::pair<texture, uint>> textures;
    };
}