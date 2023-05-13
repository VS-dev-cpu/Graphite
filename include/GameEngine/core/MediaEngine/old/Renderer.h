#pragma once

#include <GameEngine/utility/log.h>

#include <GameEngine/core/Window.h>
#include <GameEngine/utility/stb_image.h>

// TODO: Remove THIS

#include <fstream>
#include <string>
#include <map>

namespace GameEngine
{
    // OpenGL Renderer (with Window Manager)
    class Renderer : public Window
    {
    public:
        Renderer(std::string name = "GameEngine::Renderer", bool fullscreen = true, int width = 720, int height = 480);
        ~Renderer();

        void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, GLbitfield clear_buffers = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bool update();

        // 2D Renderer

        // Add Shader from File
        std::string add(std::string name, std::string vertex, std::string fragment, std::string geometry = "");

        // Add Shader from Char*
        std::string add(std::string name, const char *vertex, const char *fragment, const char *geometry = nullptr);

    public:
        bool ok = true;

    private:
        uint VAO, VBO, EBO;

        std::map<std::string, uint> shaders;

    private:
        std::string loadFromFile(std::string path, std::string ext = "")
        {
            std::ifstream file(path);
            std::string raw;

            // Open File
            if (!file.is_open())
            {
                if (ext == "")
                    return "";
                else
                {
                    file.open(path + ext);
                    if (!file.is_open())
                        return "";
                }
            }

            // Copy Data
            std::string line;
            while (getline(file, line))
                raw += line + "\n";

            file.close();

            return raw;
        }
    };
}