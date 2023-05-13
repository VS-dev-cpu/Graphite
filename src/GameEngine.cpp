#include <GameEngine/GameEngine.h>

namespace GameEngine
{
    // Initialize Engine
    GameEngine::GameEngine(std::string name, bool fullscreen, int width, int height) : me(name, fullscreen, width, height)
    {
        LOG::SYSTEM("GameEngine", "Initialized");
    }

    // Destroy Engine
    GameEngine::~GameEngine()
    {
        LOG::SYSTEM("GameEngine", "Destroyed");
    }

    // Start Engine
    void GameEngine::start()
    {
        // Start Render Thread Loop
        me.start();

        // Initialize Modules
        for (auto [name, module] : modules)
            module->init();

        LOG::SYSTEM("GameEngine", "Started Successfully");

        // Main Loop
        double past = now = time();
        while (me.running)
        {
            // Calculate DeltaTime
            past = now;
            now = time();
            deltaTime = now - past;

            double start = time(); // [MainTime] Start

            // Update Modules
            for (auto [name, module] : modules)
                module->update(deltaTime);

            // Update Render Queue
            me.update();
        }
    }

    std::string GameEngine::add(std::string name, Module *module)
    {
        module->engine = this;

        uint i = 0;
        if (modules.count(name) > 0)
        {
            while (modules.count(name + std::to_string(i)) > 0)
                i++;
            name += std::to_string(i);
        }

        modules[name] = module;
        return name;
    }
}