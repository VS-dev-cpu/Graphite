#include <Graphite/core/Media.h>

#include <Graphite/renderers/OpenGL.h>

namespace Graphite::Media {

Media::Media(std::string name, bool fullscreen, int width, int height)
    : name(name), fullscreen(fullscreen), width(width), height(height) {

    running = true;

    if (pthread_create(&renderThread, nullptr, &render, this))
        LOG::ERROR("Media", "Render Thread Failed");
    else
        LOG::SYSTEM("Media", "Renderer Initialized");
}

Media::~Media() {
    running = false;
    pthread_join(renderThread, NULL);
}

void Media::update() {
    drawable = true;
    while (drawable && running && !quit)
        ;

    renderQueue.clear();
}

void Media::exit() { quit = true; }

void Media::add(ACTION action, RenderData data) {
    renderQueue.push_back(RenderTask(action, data));
}

void *Media::render(void *arg) {
    // Detach Thread
    Media *engine = (Media *)arg;
    pthread_detach(pthread_self());

    // Initialize Renderer
    Renderer *renderer = new OpenGL();
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
                std::pair<std::string, shader> sh =
                    std::any_cast<std::pair<std::string, shader>>(data);
                // ax.shader(sh.second.vertex, sh.second.fragment,
                //           sh.second.geometry);
            } break;

            case ACTION::ADD_TEXTURE: {
                // Add Texture
                std::pair<std::string, texture> tex =
                    std::any_cast<std::pair<std::string, texture>>(data);
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
        // engine->running = ax.update();
        tasks.clear();

        if (engine->quit)
            engine->running = false;
    }

    // exit thread
    pthread_exit(nullptr);
    return nullptr;
}

} // namespace Graphite::Media