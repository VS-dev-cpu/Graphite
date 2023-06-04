#pragma once

#include <Graphite/core/MediaEngine.h>

#include <Graphite/core/log.h>
#include <Graphite/types/module.h>

#include <any>
#include <map>
#include <pthread.h>
#include <vector>

namespace Graphite {

class Engine {
  public:
    Engine(std::string name = "Graphite::Engine", bool fullscreen = true,
           int width = 720, int height = 480);

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
    MediaEngine me;

    vec2 cursor;

  private:
    // Engine Flags
    bool running = false;  // is Engine Running ?
    bool quit = false;     // should quit ?
    bool drawable = false; // Has New Drawable Content ?

    std::vector<Module *> modules; // Modules

  private:
};

} // namespace Graphite