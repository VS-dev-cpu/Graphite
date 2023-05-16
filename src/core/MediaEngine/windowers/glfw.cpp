#include <GameEngine/core/MediaEngine/windowers/glfw.h>

std::map<std::string, int> GLFW_STRING_SCANCODE = {
    {"a", glfwGetKeyScancode(GLFW_KEY_A)}};
// TODO: Scancodes

namespace GameEngine::MEDIA::WINDOWER
{
    bool GLFW::init(GRAPHICS_API api, std::string name, bool fullscreen, int width, int height)
    {
        if (isInit)
        {
            LOG::WARNING("GLFW", "Already Init");
            return true;
        }

        glfwInit();

        switch (api)
        {
        default:
            LOG::ERROR("GLFW", "%s is not supported", api == DIRECTX ? "DirectX" : (api == METAL ? "Metal" : "Unknown"));
            return isInit = false;
            break;

        case OPENGL:
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;
        }

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

        if (window == nullptr)
        {
            LOG::ERROR("GLFW", "Failed to Create Window");
            glfwTerminate();
            return isInit = false;
        }

        switch (api)
        {
        case OPENGL:
            glfwMakeContextCurrent(window);

            // Load OpenGL
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                LOG::ERROR("GLFW", "Failed to Initialize Renderer (OpenGL)");
                return isInit = false;
            }
            break;

        default:
            LOG::ERROR("GLFW", "Unexpected Error");
            return isInit = false;
            break;
        }

        glfwSetWindowUserPointer(window, this);

        // Set Callbacks
        glfwSetFramebufferSizeCallback(window, callback_resize);
        glfwSetKeyCallback(window, callback_key);
        glfwSetCursorPosCallback(window, callback_cursor);
        glfwSetScrollCallback(window, callback_scroll);

        return isInit = true;
    }

    bool GLFW::clean()
    {
        glfwDestroyWindow(window);
        glfwTerminate();

        return !(isInit = false);
    }

    bool GLFW::update()
    {
        // Update GLFW
        glfwSwapBuffers(window);

        // Poll Events
        glfwPollEvents();

        glfwGetFramebufferSize(window, &width, &height);

        return !glfwWindowShouldClose(window);
    }

    bool GLFW::key(std::string k)
    {
        return keyboard.count(GLFW_STRING_SCANCODE[k]) > 0;
    }
}