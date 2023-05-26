#include "Artifex/Artifex.h"
#include <GameEngine/core/MediaEngine/MediaEngine.h>

namespace GameEngine::MEDIA {
MediaEngine::MediaEngine(std::string name, bool fullscreen, int width,
                         int height)
    : name(name), fullscreen(fullscreen), width(width), height(height) {
    // Initialize Windower & Renderer
    // windower = new WINDOWER::GLFW;
    // renderer = new RENDERER::OpenGL;

    running = true;

    // Initialize Render Thread
    if (pthread_create(&renderThread, nullptr, &render, this))
        LOG::ERROR("MediaEngine", "Render Thread Failed");
    else
        LOG::SYSTEM("MediaEngine", "Renderer Initialized");
}

MediaEngine::~MediaEngine() {
    // Stop Threads
    running = false;
    pthread_join(renderThread, NULL);
}

void MediaEngine::update() {
    drawable = true;
    while (drawable && running && !quit)
        ;

    renderQueue.clear();
}

void MediaEngine::exit() { quit = true; }

void MediaEngine::add(ACTION::ENUM action, RenderData data) {
    renderQueue.push_back(RenderTask(action, data));
}

void *MediaEngine::render(void *arg) {
    // Detach Thread
    MediaEngine *engine = (MediaEngine *)arg;
    pthread_detach(pthread_self());

    // Initialize Renderer
    Artifex ax(engine->name, engine->width, engine->height);
    ax.fullscreen(engine->fullscreen);

    // Main Render Loop
    while (engine->running) {
        while (!engine->drawable && engine->running && !engine->quit)
            ;

        auto tasks = engine->renderQueue; // TODO: fix RenderQueue Issue
        engine->drawable = false;

        // Draw Render Queue (content)
        for (auto [action, data] : tasks) {
            switch (action) {
            default:
                // Invalid ENUM
                LOG::WARNING("RenderThread", "Invalid Enum: %i", action);
            case ACTION::PASS: {
                // Do Nothing
            } break;

                // Basic Management

            case ACTION::SLEEP: {
                // Sleep
                float amount = std::any_cast<float>(data);
                float start = time();
                while (time() - start < amount)
                    ;
            } break;

            case ACTION::PRINT: {
                // Print Debug Message
                std::string str = std::any_cast<std::string>(data);
                LOG::DEBUG("RenderQueue", str.c_str());
            } break;

                // Window Management

            case ACTION::SET_FULLSCREEN: {
                // Make Window Fullscreen
                bool en = std::any_cast<bool>(data);
                ax.fullscreen(en);
            }

            case ACTION::SET_VSYNC: {
                // Set VSync Level
                int level = std::any_cast<int>(data);
                ax.vsync(level);
            } break;

                // Resource Managing

            case ACTION::ADD_SHADER: {
                // Add Shader
                std::pair<std::string, shader> sh =
                    std::any_cast<std::pair<std::string, shader>>(data);
                ax.shader(sh.second.vertex, sh.second.fragment,
                          sh.second.geometry);
            } break;

            case ACTION::ADD_TEXTURE: {
                // Add Texture
                std::pair<std::string, texture> tex =
                    std::any_cast<std::pair<std::string, texture>>(data);
                ax.texture(tex.second.data, tex.second.width, tex.second.height,
                           tex.second.nrChannels);
            } break;

                // Rendering

            case ACTION::CLEAR: {
                // Clear Screen
                vec3 color = std::any_cast<vec3>(data);
                ax.clear(color.x, color.y, color.z);
            } break;

            case ACTION::DRAW_TEXTURE: {
                // Draw Texture
                auto [name, center, size, rotation] =
                    std::any_cast<std::tuple<std::string, vec2, vec2, float>>(
                        data);
                // TODO: Draw Texture
            } break;
            }
        }

        // Update Screen
        engine->running = ax.update();
        tasks.clear();

        if (engine->quit)
            engine->running = false;
    }

    // exit thread
    pthread_exit(nullptr);
    return nullptr;
}
} // namespace GameEngine::MEDIA