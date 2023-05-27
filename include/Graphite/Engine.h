#pragma once

#include <Graphite/core/log.h>

#include <Graphite/core/PhysicsEngine/PhysicsEngine.h>

#include <Graphite/types/module.h>

#include <Graphite/core/Media.h>

#include <any>
#include <map>
#include <pthread.h>
#include <vector>

namespace Graphite {

class Engine {
  public:
    // Initialize Game Engine
    Engine(std::string name = "Graphite::Engine", bool fullscreen = true,
           int width = 720, int height = 480);

    // Destroy Game Engine
    ~Engine();

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
    Media::Media me;

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
} // namespace Graphite