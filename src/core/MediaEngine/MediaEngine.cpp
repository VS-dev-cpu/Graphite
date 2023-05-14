#include <GameEngine/core/MediaEngine/MediaEngine.h>

namespace GameEngine::MEDIA
{
    MediaEngine::MediaEngine(std::string name, bool fullscreen, int width, int height) : name(name), fullscreen(fullscreen), width(width), height(height)
    {
        // Try to create Mixer Thread
        int err = pthread_create(&mixerThread, nullptr, &mix, this);

        if (err != 0)
            LOG::ERROR("MediaEngine", "Mixer Thread Failed");
        else
            LOG::SYSTEM("MediaEngine", "Mixer Initialized");

        // Try to create Render Thread
        err = pthread_create(&renderThread, nullptr, &render, this);

        if (err != 0)
            LOG::ERROR("MediaEngine", "Render Thread Failed");
        else
            LOG::SYSTEM("MediaEngine", "Renderer Initialized");
    }

    MediaEngine::~MediaEngine()
    {
        // Stop Threads
        running = false;
        pthread_join(mixerThread, NULL);
        pthread_join(renderThread, NULL);
    }

    void MediaEngine::start(bool multithreading)
    {
        running = true;
    }

    void MediaEngine::update()
    {
        // Push Render Queue
        drawable = true;
        while (drawable)
            if (!running)
                return;

        renderQueue.clear();

        // TODO: Check if renderthread stopped
    }

    void MediaEngine::reset()
    {
        // Stop Threads
        running = false;
        pthread_join(mixerThread, NULL);
        pthread_join(renderThread, NULL);

        // Restart Mixer Thread
        int err = pthread_create(&mixerThread, nullptr, &mix, this);

        if (err == 0)
            // Everything is ok
            LOG::SYSTEM("MediaEngine", "Restarted Mixer Thread");
        else
            // render thread is not ok
            LOG::ERROR("MediaEngine", "Failed to restart Mixer Thread");

        // Restart Render Thread
        err = pthread_create(&renderThread, nullptr, &render, this);

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

    void *MediaEngine::mix(void *arg)
    {
        MediaEngine *engine = (MediaEngine *)arg;
        pthread_detach(pthread_self());

        // Wait for Engine to Start
        while (!engine->running)
            ;

        // Initialize Mixer
        Mixer *mixer;

        if (true)
            mixer = new MIXER::OpenAL();

        if (!mixer->ok)
            LOG::ERROR("MixerThread", "Failed to start Mixer");

        // Main Mixer Loop
        while (engine->running)
        {
            // TODO: Mix
        }

        delete mixer;
        mixer = nullptr;

        // exit thread
        pthread_exit(nullptr);
        return nullptr;
    }

    void *MediaEngine::render(void *arg)
    {
        MediaEngine *engine = (MediaEngine *)arg;
        pthread_detach(pthread_self());

        // Wait for Engine to Start
        while (!engine->running)
            ;
        // TODO: Check if Engine Stopped

        // Initialize Renderer
        Renderer *renderer;

        if (true)
            renderer = new RENDERER::OpenGL(engine->name, engine->fullscreen, engine->width, engine->height);

        if (!renderer->ok)
            LOG::ERROR("RenderThread", "Failed to start Renderer");

        // Main Render Loop
        while (engine->running)
        {
            // Get Render Queue
            while (!engine->drawable)
                if (!engine->running)
                    return 0;

            auto tasks = engine->renderQueue;
            engine->drawable = false;
            // TODO: Check if Engine Stopped

            // Draw Render Queue (content)
            for (auto [action, data] : tasks)
            {
                switch (action)
                {
                default:
                case ACTION::PASS:
                {
                    // Do Nothing
                    // PASS or Invalid ENUM
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
                }
            }

            // Update Screen
            engine->running = renderer->update();
            engine->renderQueue.clear();
        }

        delete renderer;
        renderer = nullptr;

        // exit thread
        pthread_exit(nullptr);
        return nullptr;
    }
}