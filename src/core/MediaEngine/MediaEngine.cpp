#include <GameEngine/core/MediaEngine/MediaEngine.h>

namespace GameEngine::MEDIA
{
    MediaEngine::MediaEngine(std::string name, bool fullscreen, int width, int height) : name(name), fullscreen(fullscreen), width(width), height(height)
    {
    }

    MediaEngine::~MediaEngine()
    {
        // Stop Threads
        running = false;
        pthread_join(renderThread, NULL);
    }

    void MediaEngine::start(GRAPHICS_API gAPI, bool multithreading)
    {
        running = true;
        api = gAPI;

        // Try to create Render Thread
        int err = pthread_create(&renderThread, nullptr, &render, this);

        if (err != 0)
            LOG::ERROR("MediaEngine", "Render Thread Failed");
        else
            LOG::SYSTEM("MediaEngine", "Renderer Initialized");
    }

    void MediaEngine::update()
    {
        drawable = true;
        while (drawable)
            ;

        renderQueue.clear();
    }

    void MediaEngine::exit()
    {
        quit = true;
    }

    void MediaEngine::reset(GRAPHICS_API gAPI)
    {
        api = gAPI;

        // Stop Threads
        running = false;
        pthread_join(renderThread, NULL);

        // Restart Render Thread
        int err = pthread_create(&renderThread, nullptr, &render, this);

        if (err == 0)
            // Everything is ok
            LOG::SYSTEM("MediaEngine", "Restarted Render Thread");
        else
            // render thread is not ok
            LOG::ERROR("MediaEngine", "Failed to restart Render Thread");
    }

    void MediaEngine::add(ACTION::ENUM action, RenderData data)
    {
        renderQueue.push_back(RenderTask(action, data));
    }

    void *MediaEngine::render(void *arg)
    {
        // Detach Thread
        MediaEngine *engine = (MediaEngine *)arg;
        pthread_detach(pthread_self());

        // Initialize Windower
        Windower *windower = new WINDOWER::GLFW;
        if (!windower->init(engine->api, engine->name, engine->fullscreen, engine->width, engine->height))
            LOG::ERROR("MediaEngine", "Failed to init Windower");

        // Initialize Renderer
        Renderer *renderer;

        switch (engine->api)
        {
        default:
            LOG::WARNING("MediaEngine::RenderThread", "Unknown Renderer");
        case OPENGL:
            renderer = new RENDERER::OpenGL;
            break;
        }

        renderer->init(windower);

        if (!renderer->isInit)
            LOG::ERROR("MediaEngine::RenderThread", "Failed to init Renderer");

        // Main Render Loop
        while (engine->running)
        {
            while (!engine->drawable)
                ;

            auto tasks = engine->renderQueue; // TODO: fix RenderQueue Issue
            engine->drawable = false;

            // Draw Render Queue (content)
            for (auto [action, data] : tasks)
            {
                switch (action)
                {
                default:
                    // Invalid ENUM
                    LOG::WARNING("RenderThread", "Invalid Enum: %i", action);
                case ACTION::PASS:
                {
                    // Do Nothing
                }
                break;

                case ACTION::SLEEP:
                {
                    // Sleep
                    float amount = std::any_cast<float>(data);
                    float start = time();
                    while (time() - start < amount)
                        ;
                }
                break;

                case ACTION::PRINT:
                {
                    // Print Debug Message
                    std::string str = std::any_cast<std::string>(data);
                    LOG::DEBUG("RenderQueue", str.c_str());
                }
                break;

                case ACTION::CLEAR:
                {
                    // Clear Screen
                    vec3 color = std::any_cast<vec3>(data);
                    renderer->clear(color.x, color.y, color.z);
                }
                break;

                case ACTION::ADD_SHADER:
                {
                    // Add Shader
                    std::pair<std::string, shader> sh = std::any_cast<std::pair<std::string, shader>>(data);
                    renderer->add(sh.first, sh.second);
                }
                break;

                case ACTION::ADD_TEXTURE:
                {
                    // Add Texture
                    std::pair<std::string, texture> tex = std::any_cast<std::pair<std::string, texture>>(data);
                    renderer->add(tex.first, tex.second);
                }
                break;

                case ACTION::DRAW_TEXTURE:
                {
                    // Draw Texture
                    auto [name, center, size, rotation] = std::any_cast<std::tuple<std::string, vec2, vec2, float>>(data);
                    renderer->draw_texture(name, center, size, rotation);
                }
                break;

                case ACTION::FREE_SHADER:
                {
                    // Free Shader
                    std::string sh = std::any_cast<std::string>(data);
                    renderer->free_shader(sh);
                }

                case ACTION::FREE_TEXTURE:
                {
                    // Free Texture
                    std::string tex = std::any_cast<std::string>(data);
                    renderer->free_texture(tex);
                }
                break;
                }
            }

            // Update Screen
            engine->running = renderer->update();
            tasks.clear();

            if (engine->quit)
                engine->running = false;
        }

        renderer->clean();

        // exit thread
        pthread_exit(nullptr);
        return nullptr;
    }
}