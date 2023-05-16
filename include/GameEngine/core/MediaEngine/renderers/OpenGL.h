#pragma once

#include <GameEngine/core/MediaEngine/renderers/Renderer.h>
#include <map>

// TODO: Make it Work

namespace GameEngine::MEDIA::RENDERER
{
    struct OpenGL : Renderer
    {
        bool init(Windower *wnd);
        bool clean();

        bool update();
        void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f);

        std::string add(std::string name, shader s);
        std::string add(std::string name, texture tex);

        void draw_texture(std::string name);

        void free_shader(std::string name);
        void free_texture(std::string name);

        Windower *windower = nullptr;

        // 2D Rendering
        uint VAO, VBO, EBO;

        // Shaders
        std::map<std::string, std::pair<shader, uint>> shaders;

        // Textures
        std::map<std::string, std::pair<texture, uint>> textures;
    };
}