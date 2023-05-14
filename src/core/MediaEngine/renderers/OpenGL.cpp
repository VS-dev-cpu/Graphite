#include <GameEngine/core/MediaEngine/renderers/OpenGL.h>

namespace GameEngine::MEDIA::RENDERER
{
    OpenGL::OpenGL(std::string name, bool fullscreen, int width, int height) : Renderer(name, fullscreen, width, height)
    {
        // Init Windower
        windower = new WINDOWER::GLFW(name, fullscreen, width, height);

        glfwMakeContextCurrent(windower->window);

        // Load OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG::ERROR("OpenGL", "Failed to Initialize OpenGL");
            ok = false;
            return;
        }
    }

    OpenGL::~OpenGL()
    {
    }

    bool OpenGL::update()
    {
        glViewport(0, 0, windower->width, windower->height);
        return windower->update();
    }

    void OpenGL::clear(float r, float g, float b, uint buffers)
    {
        // Clear Screen
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | buffers);
    }
}