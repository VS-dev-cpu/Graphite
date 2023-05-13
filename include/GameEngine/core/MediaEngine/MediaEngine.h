#pragma once

#include <GameEngine/core/log.h>
#include <GameEngine/types/base.h>

// Mixers
#include <GameEngine/core/MediaEngine/mixers/Mixer.h>
#include <GameEngine/core/MediaEngine/mixers/OpenAL.h>

// Renderers
#include <GameEngine/core/MediaEngine/renderers/Renderer.h>
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
            PASS,  // Do Nothing [TM]
            SLEEP, // Sleep Some Time
            PRINT, // Print out a String (for Debugging)

            // Resource Loading
            ADD_SHADER,  // Add Shader
            ADD_TEXTURE, // Add Texture
            ADD_MESH,    // Add Mesh

            // Resource Freeing
            FREE_SHADER,  // Free Shader
            FREE_TEXTURE, // Free Texture
            FREE_MESH,    // Free Mesh

            // Rendering
            CLEAR,        // Clear Screen
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
        void start(bool multithreading = true);

        // Wait for RenderThread and pass new list
        void update();

        // Reset MediaEngine
        void reset();

        // Add Action to Queue
        void add(ACTION::ENUM action, RenderData data);

    public:
        // Window Properties
        std::string name;
        bool fullscreen;
        int width, height;

        bool running = false;

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