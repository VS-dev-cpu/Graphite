#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

#include <string>

namespace GameEngine::MEDIA
{
    // Base Windower Struct
    struct Windower
    {
        // Initialize Windowing Library
        virtual bool init(std::string name, bool fullscreen, int width, int height) { return false; }

        // Clean Up / Destroy Windowing Library
        virtual bool clean() { return false; }

        // Update Window
        virtual bool update() { return false; }

        // Set Fullscreen
        virtual bool fullscreen(bool en) { return false; }

        // Get Keyboard State
        virtual bool key(std::string k) { return false; }

        // Cursor Position
        vec2 mouse;

        // Scroll Position
        vec2 scroll;

        // Window Size
        int width, height;

        // Is Library Init ?
        bool isInit = false;

        // Is Fullscreened ?
        bool isFullscreen = false;
    };

    // TODO: SDL2 Windower
    // TODO: Win32, DirectWindow & X11 Windowers
}