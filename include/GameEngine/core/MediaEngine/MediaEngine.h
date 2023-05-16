#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

// Mixers
#include <GameEngine/core/MediaEngine/mixers/Mixer.h>
#include <GameEngine/core/MediaEngine/mixers/OpenAL.h>

// Windowers
#include <GameEngine/core/MediaEngine/windowers/glfw.h>

// Renderers
#include <GameEngine/core/MediaEngine/renderers/OpenGL.h>

#include <vector>
#include <variant>
#include <any>

namespace GameEngine::MEDIA
{
    class GameEngine;

    // RenderQueue Action
    namespace ACTION
    {
        enum ENUM
        {
            // Basic Management
            PASS,  // Do Nothing [TM] (void)
            SLEEP, // Sleep Some Time (float)
            PRINT, // Print out a String (std::string)

            // Resource Loading
            ADD_SHADER,  // Add Shader (std::pair<std::string, shader>)
            ADD_TEXTURE, // Add Texture std::pair<std::string, texture>
            ADD_MESH,    // Add Mesh (TODO)

            // Resource Freeing
            FREE_SHADER,  // Free Shader (std::string)
            FREE_TEXTURE, // Free Texture (std::string)
            FREE_MESH,    // Free Mesh (TODO)

            // Rendering
            CLEAR,        // Clear Screen (vec3)
            DRAW_TEXTURE, // Render Image
            DRAW_MESH,    // Render Mesh

            // TODO: Add More Functions
        };
    }

    typedef std::any RenderData;
    typedef std::pair<ACTION::ENUM, RenderData> RenderTask;

    //  The Media Engine (responsible for Windowing, Rendering and Audio)
    class MediaEngine
    {
    public:
        // Initialize Media Engine
        MediaEngine(std::string name = "MediaEngine", bool fullscreen = true, int width = 720, int height = 480);

        // Destroy Media Engine
        ~MediaEngine();

        // Start Media Engine
        void start(GRAPHICS_API gAPI = OPENGL, bool multithreading = true);

        // Wait for RenderThread and pass new list
        void update();

        void exit();

        // Reset Renderer & Mixer
        void reset(GRAPHICS_API gAPI = OPENGL);

        // Add Action to Queue
        void add(ACTION::ENUM action, RenderData data);

    public:
        // Window Properties
        std::string name;
        bool fullscreen;
        int width, height;

        GRAPHICS_API api;

        bool running = false;
        bool quit = false;

    private:
        // Mixer Thread
        pthread_t mixerThread;

        // Render Thread
        pthread_t renderThread;

        std::vector<RenderTask> renderQueue;
        bool drawable = false;

    private:
        static void *mix(void *arg);
        static void *render(void *arg);
    };
}