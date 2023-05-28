#pragma once

#include <Graphite/core/log.h>
#include <Graphite/types/base.h>

#include <any>
#include <atomic>
#include <tuple>
#include <variant>
#include <vector>

namespace Graphite::Media {

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
class Media {
  public:
    Media(std::string name = "Graphite::Media", bool fullscreen = true,
          int width = 720, int height = 480);

    ~Media();

    // Sync With RenderThread & Update RenderQueue
    void update();

    // Exit Render Loop
    void exit();

    // Add Action to Queue
    void add(ACTION action, RenderData data);

  public:
    // Window Properties
    std::string name;
    bool fullscreen;
    int width, height;

    std::atomic<bool> running = false;
    std::atomic<bool> quit = false;

    // Windower* windower;
  private:
    // Render Thread
    pthread_t renderThread;

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t renderSignal = PTHREAD_COND_INITIALIZER;

    std::atomic<bool> drawable = false;

    // Renderer *renderer;

    std::vector<RenderTask> renderQueue;

  private:
    static void *render(void *arg);
};

} // namespace Graphite::Media