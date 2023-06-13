#include <Graphite/core/MediaEngine.h>
#include <Graphite/core/Renderer.h>
#include <Graphite/renderAPI/RenderAPI.h>

#include <Graphite/renderAPI/OpenGL/OpenGL.h>
#include <Graphite/renderAPI/Vulkan/Vulkan.h>

#include <stdexcept>

namespace Graphite {

MediaEngine::MediaEngine(std::string name, bool fullscreen, int width,
                         int height)
    : name(name), fullscreen(fullscreen), width(width), height(height) {

    running = true;

    if (pthread_create(&renderThread, nullptr, &render, this))
        LOG::ERROR("MediaEngine", "Render Thread Failed");
    else
        LOG::SYSTEM("MediaEngine", "Renderer Initialized");
}

MediaEngine::~MediaEngine() {
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

void MediaEngine::add(ACTION action, RenderData data) {
    renderQueue.push_back(RenderTask(action, data));
}

void *MediaEngine::render(void *arg) {
    // ---- Detach Thread
    MediaEngine *engine = (MediaEngine *)arg;
    pthread_detach(pthread_self());

    // ---- Initialize Render API
    RenderAPI *render;

    uint32_t api = 0;
    const uint32_t apiCount = 2;

    while (!render) {
        try {
            // Init API (Vulkan > OpenGL)
            switch (api) {
            case 0:
                render = new Vulkan();
                break;

            case 1:
                render = new OpenGL();
                break;

            default:
                if (api >= apiCount)
                    api = 0;
                break;
            }
        } catch (const int &error) {
            delete render;
            render = nullptr;

            if (api < apiCount)
                api++;
            else {
                // Failed to init API
            }
        }
    }

    // ---- Renderer Initialized; Can Start

    // Artifex ax(engine->name, engine->width, engine->height);
    // ax.fullscreen(engine->fullscreen);

    // Main Render Loop
    while (engine->running) {
        while (!engine->drawable && engine->running && !engine->quit)
            ;

        auto tasks = engine->renderQueue;
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
                // ax.fullscreen(en);
            }

            case ACTION::SET_VSYNC: {
                // Set VSync Level
                int level = std::any_cast<int>(data);
                // ax.vsync(level);
            } break;

                // Resource Managing

            case ACTION::ADD_SHADER: {
                // Add Shader
                // std::pair<std::string, Shader> sh =
                //   std::any_cast<std::pair<std::string, shader>>(data);
                // ax.shader(sh.second.vertex, sh.second.fragment,
                //           sh.second.geometry);
            } break;

            case ACTION::ADD_TEXTURE: {
                // Add Texture
                std::pair<std::string, Texture> tex =
                    std::any_cast<std::pair<std::string, Texture>>(data);
                // ax.texture(tex.second.data, tex.second.width,
                // tex.second.height,
                //            tex.second.nrChannels);
            } break;

                // Rendering

            case ACTION::CLEAR: {
                // Clear Screen
                vec3 color = std::any_cast<vec3>(data);
                // ax.clear(color.x, color.y, color.z);
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
        engine->running = render->update();
        tasks.clear();

        if (engine->quit)
            engine->running = false;
    }

    // exit thread
    pthread_exit(nullptr);
    return nullptr;
}

} // namespace Graphite