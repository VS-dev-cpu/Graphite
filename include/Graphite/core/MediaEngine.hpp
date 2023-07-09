#pragma once

#include <mathutil/common.hpp>

#include <any>
#include <atomic>
#include <pthread.h>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

namespace Graphite {

//  The Media Engine (responsible for Windowing, Rendering and Audio)
class MediaEngine {
  public:
    MediaEngine(std::string name = "Graphite::MediaEngine",
                bool fullscreen = true, int width = 720, int height = 480);

    ~MediaEngine();

    // Update Window
    void update();

    // Exit Render Loop
    void exit();

    // Rendering Actions
    // TODO

    // Mixing Actions
    // TODO

  public:
    // Window Properties
    std::string name;
    bool fullscreen;
    int width, height;

    std::atomic<bool> running = false;
    std::atomic<bool> quit = false;

  private:
    // ---- Graphics

    pthread_t renderThread;
    std::atomic<bool> drawable = false;

    // ---- Audio

  private:
    // Render Thread Function
    static void *renderer(void *arg);
};

} // namespace Graphite