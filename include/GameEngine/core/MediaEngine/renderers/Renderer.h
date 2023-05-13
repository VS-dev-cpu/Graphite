#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

#include <string>

namespace GameEngine::MEDIA
{
    class Renderer
    {
    public:
        Renderer(std::string name = "Renderer", bool fullscreen = true, int width = 720, int height = 480) { LOG::SYSTEM("Renderer", "Initialized"); }
        virtual ~Renderer() { LOG::SYSTEM("Renderer", "Destroyed"); }

        virtual bool update() { return false; }
        virtual void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) {}

    public:
        bool ok = true;
    };
}