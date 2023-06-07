#pragma once

#include <Graphite/core/log.h>
#include <Graphite/types/base.h>

#include <any>
#include <atomic>
#include <pthread.h>
#include <tuple>
#include <variant>
#include <vector>

namespace Graphite {

// RenderQueue Action
enum ACTION {
    // Basic Management

    PASS,  // Do Nothing [TM] (void)
    SLEEP, // Sleep Some Time (float)
    PRINT, // Print out a String (std::string)

    // Window Managing

    SET_FULLSCREEN, // Make Window Fullscreen (bool)
    SET_VSYNC,      // Set VSync Level (int)

    // Resource Managing

    ADD_SHADER,  // Add Shader (std::pair<std::string, shader>)
    ADD_TEXTURE, // Add Texture std::pair<std::string, texture>
    ADD_MESH,    // Add Mesh (TODO)

    // Rendering

    CLEAR,        // Clear Screen (vec3)
    DRAW_TEXTURE, // Render Image
    DRAW_MESH,    // Render Mesh

    // TODO: More Functions
};

typedef std::any RenderData;
typedef std::pair<ACTION, RenderData> RenderTask;

//  The Media Engine (responsible for Windowing, Rendering and Audio)
class MediaEngine {
  public:
    MediaEngine(std::string name = "Graphite::Media", bool fullscreen = true,
                int width = 720, int height = 480);

    ~MediaEngine();

    // Sync With RenderThread & Update RenderQueue
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
    // Render Thread
    pthread_t renderThread;

    std::atomic<bool> drawable = false;

    std::vector<RenderTask> renderQueue;

  private:
    static void *render(void *arg);
    void add(ACTION action, RenderData data);
};

} // namespace Graphite