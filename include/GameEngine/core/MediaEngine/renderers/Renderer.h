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

        virtual std::string add(std::string name, shader s) { return ""; }
        virtual std::string add(std::string name, texture tex) { return ""; }

    public:
        bool ok = true;
    };
}