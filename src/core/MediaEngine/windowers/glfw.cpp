#include <GameEngine/core/MediaEngine/windowers/glfw.h>

namespace GameEngine::MEDIA::WINDOWER
{
    // KeyCodes
    std::map<std::string, int> GLFW_STRING_SCANCODE = {
        // Letters
        {"a", GLFW_KEY_A},
        {"b", GLFW_KEY_B},
        {"c", GLFW_KEY_C},
        {"d", GLFW_KEY_D},
        {"e", GLFW_KEY_E},
        {"f", GLFW_KEY_F},
        {"g", GLFW_KEY_G},
        {"h", GLFW_KEY_H},
        {"i", GLFW_KEY_I},
        {"j", GLFW_KEY_J},
        {"k", GLFW_KEY_K},
        {"l", GLFW_KEY_L},
        {"m", GLFW_KEY_M},
        {"n", GLFW_KEY_N},
        {"o", GLFW_KEY_O},
        {"p", GLFW_KEY_P},
        {"q", GLFW_KEY_Q},
        {"r", GLFW_KEY_R},
        {"s", GLFW_KEY_S},
        {"t", GLFW_KEY_T},
        {"u", GLFW_KEY_U},
        {"v", GLFW_KEY_V},
        {"w", GLFW_KEY_W},
        {"x", GLFW_KEY_X},
        {"y", GLFW_KEY_Y},
        {"z", GLFW_KEY_Z},

        // Numbers
        {"0", GLFW_KEY_0},
        {"1", GLFW_KEY_1},
        {"2", GLFW_KEY_2},
        {"3", GLFW_KEY_3},
        {"4", GLFW_KEY_4},
        {"5", GLFW_KEY_5},
        {"6", GLFW_KEY_6},
        {"7", GLFW_KEY_7},
        {"8", GLFW_KEY_8},
        {"9", GLFW_KEY_9},

        // Enter
        {"return", GLFW_KEY_ENTER},
        {"enter", GLFW_KEY_ENTER},
        {"\n", GLFW_KEY_ENTER},

        // Escape
        {"escape", GLFW_KEY_ESCAPE},
        {"esc", GLFW_KEY_ESCAPE},

        // Backspace
        {"backspace", GLFW_KEY_BACKSPACE},
        {"\b", GLFW_KEY_BACKSPACE},

        // Tab
        {"tab", GLFW_KEY_TAB},
        {"\t", GLFW_KEY_TAB},

        // Space
        {"space", GLFW_KEY_SPACE},
        {" ", GLFW_KEY_SPACE},

        // Control Keys
        {"ctrl", GLFW_KEY_LEFT_CONTROL},
        {"control", GLFW_KEY_LEFT_CONTROL},
        {"shift", GLFW_KEY_LEFT_SHIFT},
        {"alt", GLFW_KEY_LEFT_ALT},
        {"super", GLFW_KEY_LEFT_SUPER},

        {"lctrl", GLFW_KEY_LEFT_CONTROL},
        {"lshift", GLFW_KEY_LEFT_SHIFT},
        {"lalt", GLFW_KEY_LEFT_ALT},
        {"lgui", GLFW_KEY_LEFT_SUPER},
        {"lsuper", GLFW_KEY_LEFT_SUPER},

        {"rctrl", GLFW_KEY_RIGHT_CONTROL},
        {"rshift", GLFW_KEY_RIGHT_SHIFT},
        {"ralt", GLFW_KEY_RIGHT_ALT},
        {"rgui", GLFW_KEY_RIGHT_SUPER},
        {"rsuper", GLFW_KEY_RIGHT_SUPER},

        // Function Keys
        {"f1", GLFW_KEY_F1},
        {"f2", GLFW_KEY_F2},
        {"f3", GLFW_KEY_F3},
        {"f4", GLFW_KEY_F4},
        {"f5", GLFW_KEY_F5},
        {"f6", GLFW_KEY_F6},
        {"f7", GLFW_KEY_F7},
        {"f8", GLFW_KEY_F8},
        {"f9", GLFW_KEY_F9},
        {"f10", GLFW_KEY_F10},
        {"f11", GLFW_KEY_F11},
        {"f12", GLFW_KEY_F12},
    };

    bool GLFW::init(std::string name, bool fullscreen_, int width, int height)
    {
        if (isInit)
        {
            LOG::WARNING("GLFW", "Already Init");
            return true;
        }

        glfwInit();

        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

        if (window == nullptr)
        {
            LOG::ERROR("GLFW", "Failed to Create Window");
            glfwTerminate();
            return isInit = false;
        }

        glfwMakeContextCurrent(window);

        // Init OpenGL
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            
        // Load OpenGL
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG::ERROR("GLFW", "Failed to Initialize Renderer (OpenGL)");
            return isInit = false;
        }

        glfwSetWindowUserPointer(window, this);

        // Set Callbacks
        glfwSetFramebufferSizeCallback(window, callback_resize);
        glfwSetKeyCallback(window, callback_key);
        glfwSetCursorPosCallback(window, callback_cursor);
        glfwSetScrollCallback(window, callback_scroll);

        glfwSwapInterval(0);

        fullscreen(fullscreen_);

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

    bool GLFW::fullscreen(bool en)
    {
        GLFWmonitor* monitor = glfwGetWindowMonitor(window);
        const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        if (en)
        {
            small_size[0] = width;
            small_size[1] = height;
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, videoMode->width, videoMode->height, GLFW_DONT_CARE);

        }
        else
            glfwSetWindowMonitor(window, nullptr, 0, 0, small_size[0], small_size[1], GLFW_DONT_CARE);

        isFullscreen = en;
    }

    bool GLFW::key(std::string k)
    {
        return keyboard.count(glfwGetKeyScancode(GLFW_STRING_SCANCODE[k])) > 0;
    }
}