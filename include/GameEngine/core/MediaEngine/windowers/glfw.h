#pragma once

#include <GameEngine/core/MediaEngine/windowers/Windower.h>

// Include Renderers
#include <GameEngine/utility/glad.h>
#define GLFW_INCLUDE_VULKAN

// Include Windowing Library
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <set>

namespace GameEngine::MEDIA::WINDOWER
{
    // GLFW Windowing Library
    struct GLFW : Windower
    {
        // Initialize GLFW
        bool init(std::string name = "GLFW Window", bool fullscreen = true, int width = 1920, int height = 1080);

        // Destroy Window
        bool clean();

        // Update Window
        bool update();

        // Get Keyboard State
        bool key(std::string k);

        // Keyboard State
        std::set<int> keyboard;

        // Window
        GLFWwindow *window = nullptr;
        GLFWmonitor *monitor = nullptr;

        // FrameBuffer Size Callback
        static void callback_resize(GLFWwindow *window, int w, int h)
        {
            GLFW *self = (GLFW *)glfwGetWindowUserPointer(window);
            self->width = w;
            self->height = h;
        }

        // Keyboard State Callback
        static void callback_key(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            GLFW *self = (GLFW *)glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS)
                self->keyboard.insert(scancode);
            else
                self->keyboard.erase(scancode);
        }

        // Cursor Movement Callback
        static void callback_cursor(GLFWwindow *window, double x, double y)
        {
            GLFW *self = (GLFW *)glfwGetWindowUserPointer(window);

            self->mouse.x = (x * 2.0f) / (float)self->width - 1.0f;
            self->mouse.y = (y * -2.0f) / (float)self->height + 1.0f;
        }

        // Scroll Movement Callback
        static void callback_scroll(GLFWwindow *window, double x, double y)
        {
            GLFW *self = (GLFW *)glfwGetWindowUserPointer(window);

            self->scroll.x = x;
            self->scroll.y = y;
        }
    };
}