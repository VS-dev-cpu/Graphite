#pragma once

#include <GameEngine/core/log.h>
#include <string>

namespace GameEngine
{
    class GameEngine;

    // A Module (aka Extension/Addon)
    class Module
    {
    public:
        // ---- Variables ----

        GameEngine *engine = nullptr; // hosting Game Engine
        std::string name;             // Module's Name

        // ---- Management ----

        virtual void init(){};    // called on init
        virtual void destroy(){}; // called before destroying

        // ---- Updates ----

        virtual void update(float deltaTime){};       // called on update
        virtual void fixedUpdate(double deltaTime){}; // called on in every 16 ms (60 fps)

        // ---- Event Callbacks ----

        virtual void onKeyPress(uint pressedKey){};                 // called on key press
        virtual void onKeyRelease(uint releasedKey){};              // called on every key release
        virtual void onMouseMovement(float mouseX, float mouseY){}; // called on mouse movement
        virtual void onSceneChange(std::string newScene){};         // called on scene change
    };
}