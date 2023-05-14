#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

#include <string>

namespace GameEngine::MEDIA
{
    class Renderer
    {
    public:
        virtual bool update() { return false; }
        virtual void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) {}

    public:
        bool ok = true;
    };
}