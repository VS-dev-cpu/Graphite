#include <GameEngine/core/MediaEngine/windowers/glfw.h>

std::map<std::string, int> GLFW_STRING_SCANCODE = {
    {"a", glfwGetKeyScancode(GLFW_KEY_A)}};
// TODO: Scancodes

namespace GameEngine::MEDIA::WINDOWER
{
    GLFW::GLFW(std::string name, bool fullscreen, int width, int height)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

        if (window == nullptr)
        {
            LOG::ERROR("GLFW", "Failed to Create GLFW");
            glfwTerminate();
            ok = false;
            return;
        }

        glfwSetWindowUserPointer(window, this);

        // Set Callbacks
        // no glfwSetWindowSizeCallback(window, callback_resize);
        glfwSetFramebufferSizeCallback(window, callback_resize);
        // no glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
        // no glfwSetWindowPosCallback(window, window_pos_callback);

        glfwSetKeyCallback(window, callback_key);
        glfwSetCursorPosCallback(window, callback_cursor);
        glfwSetScrollCallback(window, callback_scroll);

        // TODO: Joystick Input

        // Fullscreen, if needed
        setFullscreen(fullscreen);

        setVSync(0);
    }

    GLFW::~GLFW()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
    }

    bool GLFW::update()
    {
        // Update GLFW
        glfwSwapBuffers(window);

        // Poll Events
        glfwPollEvents();

        return !glfwWindowShouldClose(window);
    }

    bool GLFW::setFullscreen(bool fullscreen)
    {
        if (isFullscreen() == fullscreen)
            return true;

        if (fullscreen)
        {
            // Get Monitor, if not set
            if (monitor == nullptr)
                monitor = glfwGetPrimaryMonitor();

            // Exit if monitor is unavailable
            if (monitor == nullptr)
                return false;

            // backup window position and window size
            glfwGetWindowPos(window, &windowPos[0], &windowPos[1]);
            glfwGetWindowSize(window, &width, &height);

            // get resolution of monitor
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);

            // switch to full screen
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
        }
        else
        {
            // restore last window size and position
            glfwSetWindowMonitor(window, nullptr, windowPos[0], windowPos[1], width, height, 0);
        }

        return true;
    }

    bool GLFW::key(std::string k)
    {
        return keyboard.count(GLFW_STRING_SCANCODE[k]) > 0;
    }
}