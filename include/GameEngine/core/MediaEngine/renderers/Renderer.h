#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

#include <GameEngine/core/MediaEngine/windowers/Windower.h>

#include <string>

namespace GameEngine::MEDIA
{
    // Base Renderer Struct
    struct Renderer
    {
        // Initialize Renderer
        virtual bool init(Windower *wnd) { return false; }
        virtual bool clean() { return false; }

        virtual bool update() { return false; }
        virtual void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f) {}

        virtual std::string add(std::string name, shader s) { return ""; }
        virtual std::string add(std::string name, texture tex) { return ""; }

        virtual void draw_texture(std::string name) {}

        virtual void free_shader(std::string name) {}
        virtual void free_texture(std::string name) {}

        // Is Library Init ?
        bool isInit = false;
    };
}