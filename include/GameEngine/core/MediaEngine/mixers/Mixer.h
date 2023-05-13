#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

#include <string>

namespace GameEngine::MEDIA
{
    class Mixer
    {
    public:
        Mixer() { LOG::SYSTEM("Mixer", "Initialized"); }
        virtual ~Mixer() { LOG::SYSTEM("Mixer", "Destroyed"); }

        virtual bool update() { return false; }
        virtual void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) {}

    public:
        bool ok = true;
    };
}