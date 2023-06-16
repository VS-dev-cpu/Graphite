#pragma once

#include <Graphite/core/log.h>
#include <Graphite/types/base.h>

#include <Graphite/audio/AudioAPI.h>
#include <Graphite/graphics/GraphicsAPI.h>

#include <any>
#include <atomic>
#include <pthread.h>
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

    // Graphics API
    GraphicsAPI *render = nullptr;

    // Audio API
    AudioAPI *mix = nullptr;

  private:
    // ---- Graphics

    pthread_t renderThread;
    std::atomic<bool> drawable = false;

    // ---- Audio

  private:
    // Initialize Graphics API
    void initGraphics(uint32_t api = 0);

    // Initialize Audio API
    void initAudio(uint32_t api = 0);

    // Render Thread Function
    static void *renderer(void *arg);
};

} // namespace Graphite