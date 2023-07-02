#pragma once

#include <Graphite/types/module.hpp>

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

    // Add Module
    uint add(Module *module);

  public:
    // Timing
    double now, deltaTime;

    MediaEngine me;

    vec2 cursor;

  private:
    // Engine Flags
    bool running = false;
    bool quit = false;
    bool drawable = false;

    std::vector<Module *> modules;

  private:
};

} // namespace Graphite