#pragma once

#include <GameEngine/core/tools/log.h>

#include <GameEngine/core/PhysicsEngine/PhysicsEngine.h>

#include <GameEngine/types/module.h>

#include <GameEngine/core/MediaEngine/MediaEngine.h>

#include <any>
#include <map>
#include <pthread.h>
#include <vector>

namespace GameEngine {
// Main Game Engine (responsible for Managing Modules, Holding everything
// together)
class GameEngine {
  public:
    // Initialize Game Engine
    GameEngine(std::string name = "GameEngine::GameEngine",
               bool fullscreen = true, int width = 720, int height = 480);

    // Destroy Game Engine
    ~GameEngine();

    // Start Main Game Loop
    void start();

    // Get Key State
    bool key(std::string k);

    // Add Module (Script)
    uint add(Module *module);

  public:
    // Main Thread Timing
    double now, deltaTime;

    // Media Engine
    MEDIA::MediaEngine me;

    vec2 cursor;

  private:
    // Main Physics Engine
    Physics physics;

    // Engine Flags
    bool running = false;  // is Engine Running ?
    bool quit = false;     // should quit ?
    bool drawable = false; // Has New Drawable Content ?

    std::vector<Module *> modules; // Modules

  private:
};
} // namespace GameEngine