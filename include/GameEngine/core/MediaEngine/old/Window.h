#pragma once

#include <GameEngine/utility/log.h>

#include <GameEngine/utility/glad.h>
#include <GLFW/glfw3.h>

// Detect OS
#if defined(__linux)
#define __pc
#elif defined(__WIN32)
#define __window
#define __pc

#undef ERROR
#undef near
#undef far
#elif defined(__EMSCRIPTEN__)
#define __browser
#include <emscripten.h>
#include <emscripten/html5.h>
#else
// #define __mobile
// #define __macos
#warning Targeted OS is not recognized
#endif

#include <string>
#include <map>
#include <set>

namespace GameEngine
{
    // OpenGL Window (& Input) Manager
    class Window
    {
    public:
        Window(std::string name = "GameEngine::Window", bool fullscreen = true, int width = 720, int height = 480);
        ~Window();

        bool update();

        bool isFullscreen() { return glfwGetWindowMonitor(window) != nullptr; };
        bool setFullscreen(bool fullscreen);
        void setTitle(std::string title) { glfwSetWindowTitle(window, title.c_str()); };
        void setIcon(int n, GLFWimage *icon) { glfwSetWindowIcon(window, n, icon); };

        void setVSync(int en) { glfwSwapInterval(en); };

        void maximize() { glfwMaximizeWindow(window); };
        void minimize() { glfwIconifyWindow(window); };
        void restore() { glfwRestoreWindow(window); };

        void show() { glfwShowWindow(window); };
        void hide() { glfwHideWindow(window); };

        void focus() { glfwFocusWindow(window); };
        void transparent(bool en = false) { glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, en); };
        void opacity(float value = 1.0f) { glfwSetWindowOpacity(window, value); };
        void resizeable(bool en = true) { glfwSetWindowAttrib(window, GLFW_RESIZABLE, en); };
        void decorated(bool en = true) { glfwSetWindowAttrib(window, GLFW_DECORATED, en); };
        void autoMinimize(bool en = false) { glfwSetWindowAttrib(window, GLFW_AUTO_ICONIFY, en); };
        void alwaysOnTop(bool en = false) { glfwSetWindowAttrib(window, GLFW_FLOATING, en); };
        void focusOnShow(bool en = false) { glfwSetWindowAttrib(window, GLFW_FOCUS_ON_SHOW, en); };

        void hideCursor(bool en = true) { glfwSetInputMode(window, GLFW_CURSOR, en ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL); };

        void close(bool sure = true) { glfwSetWindowShouldClose(window, sure); };

        bool key(std::string k);

    public:
        bool ok = true;

        // Cursor & Scroll Positions
        double cursor[2], scroll[2];

    protected:
        // Window Size
        int width, height;

    private:
        GLFWwindow *window = nullptr;
        GLFWmonitor *monitor = nullptr;

        bool shouldResize = true;

        // Window Position & Size
        int windowPos[2];

        // Keyboard State
        std::set<int> keyboard;

    private:
        // FrameBuffer Size Callback
        static void callback_resize(GLFWwindow *window, int w, int h)
        {
            Window *self = (Window *)glfwGetWindowUserPointer(window);
            self->shouldResize = true;
        }

        // Keyboard State Callback
        static void callback_key(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            Window *self = (Window *)glfwGetWindowUserPointer(window);

            if (action == GLFW_PRESS)
                self->keyboard.insert(scancode);
            else
                self->keyboard.erase(scancode);
        }

        // Cursor Movement Callback
        static void callback_cursor(GLFWwindow *window, double x, double y)
        {
            Window *self = (Window *)glfwGetWindowUserPointer(window);

            self->cursor[0] = (x * 2.0) / (double)self->width - 1.0;
            self->cursor[1] = (y * -2.0) / (double)self->height + 1.0;
        }

        // Scroll Movement Callback
        static void callback_scroll(GLFWwindow *window, double x, double y)
        {
            Window *self = (Window *)glfwGetWindowUserPointer(window);

            self->scroll[0] = x;
            self->scroll[1] = y;
        }
    };
}