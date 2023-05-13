#pragma once

#include <GameEngine/core/log.h>

// TODO: Remove #include <GameEngine/core/Renderer.h>
#include <GameEngine/core/PhysicsEngine/PhysicsEngine.h>

#include <GameEngine/types/module.h>

// Include Renderers
#include <GameEngine/core/MediaEngine/MediaEngine.h>

#include <pthread.h>
#include <vector>
#include <map>
#include <any>

namespace GameEngine
{
    // Main Game Engine (responsible for Managing Modules, Holding everything together)
    class GameEngine
    {
    public:
        // Initialize Game Engine
        GameEngine(std::string name = "GameEngine::GameEngine", bool fullscreen = true, int width = 720, int height = 480);

        // Destroy Game Engine
        ~GameEngine();

        // Start Main Game Loop
        void start();

        // Add Game Module
        std::string add(std::string name, Module *module);

    public:
        // Main Thread Timing
        double now, deltaTime;

    private:
        // Media Engine
        MEDIA::MediaEngine me;

        // Main Physics Engine
        Physics physics;

        // Engine Flags
        bool running = false;  // is Engine Running ?
        bool drawable = false; // Has New Drawable Content ?

        std::map<std::string, Module *> modules; // Game Engine Modules

    private:
    };
}