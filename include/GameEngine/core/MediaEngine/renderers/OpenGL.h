#pragma once

#include <GameEngine/core/MediaEngine/renderers/Renderer.h>

// TODO: Make it Work

namespace GameEngine::MEDIA::RENDERER
{
    class OpenGL : public Renderer
    {
    public:
        OpenGL(std::string name = "RENDERER::OpenGL", bool fullscreen = true, int width = 720, int height = 480) : Renderer(name, fullscreen, width, height) {}

    private:
    };
}