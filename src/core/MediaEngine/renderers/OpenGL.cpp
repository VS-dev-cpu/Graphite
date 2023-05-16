#include <GameEngine/core/MediaEngine/renderers/OpenGL.h>

#include <GameEngine/utility/glad.h>

namespace GameEngine::MEDIA::RENDERER
{
    bool OpenGL::init(Windower *wnd)
    {
        windower = wnd;

        shader s;
        s.vertex = "#version 300 es\n "
                   "layout(location = 0) in vec2 aPos;\n"
                   "layout(location = 1) in vec2 aTexCoord;\n"
                   "out vec2 TexCoord;\n"
                   "out vec2 FragPos;\n"
                   "uniform vec2 center;\n"
                   "uniform vec2 size;\n"
                   "uniform float rotation;\n"
                   "uniform vec2 ratio;\n"
                   "void main()\n"
                   "{\n"
                   "    float rads = radians(-rotation);\n"
                   "    vec2 point = vec2(size.x * aPos.x, size.y * aPos.y);\n"
                   "    float x = cos(rads) * (point.x) - sin(rads) * (point.y) + center.x;\n"
                   "    float y = sin(rads) * (point.x) + cos(rads) * (point.y) + center.y;\n"
                   "    x *= ratio.x;\n"
                   "    y *= ratio.y;\n"
                   "    TexCoord = aTexCoord;\n"
                   "    FragPos = vec2(aPos.x, aPos.y);\n"
                   "    gl_Position = vec4(x, y, 0.0, 1.0);\n"
                   "}\n";

        s.fragment = "#version 300 es\n"
                     "precision mediump float;\n"
                     "out vec4 FragColor;\n"
                     "in vec2 TexCoord;\n"
                     "in vec2 FragPos;\n"
                     "uniform sampler2D tex;\n"
                     "void main()\n"
                     "{\n"
                     "    FragColor = texture(tex, TexCoord);\n"
                     "}";

        // Failed to Init Shader
        if (add("__default", s) == "")
        {
            LOG::ERROR("OpenGL", "Failed to load 2D Shader");
            return isInit = false;
        }

        // Load 2D Renderer
        float vertices[] = {
            // positions      // texture coords
            -1.0f, 1.0f, 0.0f, 1.0f,  // top right
            -1.0f, -1.0f, 0.0f, 0.0f, // bottom right
            1.0f, -1.0f, 1.0f, 0.0f,  // bottom left
            1.0f, 1.0f, 1.0f, 1.0f    // top left
        };

        uint indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Config OpenGL
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);

        return isInit = true;
    }

    bool OpenGL::clean()
    {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);

        // Free Textures
        for (auto [name, tex] : textures)
        {
            free(tex.first.data);
            glDeleteTextures(1, &tex.second);
        }

        // Free Shaders
        for (auto [name, sh] : shaders)
            glDeleteShader(sh.second);

        LOG::SYSTEM("OpenGL", "Cleanup Finished");

        return true;
    }

    bool OpenGL::update()
    {
        return windower->update();
    }

    void OpenGL::clear(float r, float g, float b)
    {
        // Clear Screen
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    std::string OpenGL::add(std::string name, shader s)
    {
        const char *vertex = s.vertex.c_str();
        const char *fragment = s.fragment.c_str();
        const char *geometry = s.geometry == "" ? nullptr : s.geometry.c_str();

        // Compile & Load Shader
        uint vert, frag, geo, id;
        bool isGeo = geometry != nullptr;

        int success;
        char infoLog[1024];

        // ---- Compile Vertex Shader
        vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &vertex, NULL);
        glCompileShader(vert);

        glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vert, 1024, NULL, infoLog);
            LOG::ERROR("OpenGL", "Failed to compile Vertex shader (%s): \n%s", name.c_str(), infoLog);
            return "";
        }

        // ---- Compile Fragment Shader
        frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &fragment, NULL);
        glCompileShader(frag);

        glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(frag, 1024, NULL, infoLog);
            LOG::ERROR("OpenGL", "Failed to compile Fragment shader (%s): 'n%s", name.c_str(), infoLog);
            glDeleteShader(vert);
            return "";
        }

        if (isGeo)
        {
            // ---- Compile Geometry Shader
            geo = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(geo, 1, &geometry, NULL);
            glCompileShader(geo);

            glGetShaderiv(geo, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(geo, 1024, NULL, infoLog);
                LOG::WARNING("OpenGL", "Failed to compile Geometry shader (%s): \n%s", name.c_str(), infoLog);
                isGeo = false;
            }
        }

        // ---- Create Shader Program
        id = glCreateProgram();
        glAttachShader(id, vert);
        glAttachShader(id, frag);
        if (isGeo)
            glAttachShader(id, geo);

        glLinkProgram(id);

        // Delete unnecessary shaders
        glDeleteShader(vert);
        glDeleteShader(frag);
        if (isGeo)
            glDeleteShader(geo);

        // Check if linking was successful
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            LOG::ERROR("OpenGL", "Failed to link Shaders (%s): \n%s", name.c_str(), infoLog);
            return "";
        }

        uint i = 0;
        if (shaders.count(name) > 0)
        {
            while (shaders.count(name + std::to_string(i)) > 0)
                i++;
            name += std::to_string(i);
        }

        LOG::SYSTEM("OpenGL", "Loaded Shader (%s)", name.c_str());
        shaders[name] = std::pair<shader, uint>(s, id);
        return name;
    }

    std::string OpenGL::add(std::string name, texture t)
    {
        uint id;
        if (t.data)
        {
            // Generate Empty Texture
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            // Select Color Mode
            uint mode = GL_RGB;
            switch (t.nrChannels)
            {
            default:
            case 0:
                LOG::WARNING("OpenGL", "Invalid Texture Channel(s)");
                break;

            case 1:
                mode = GL_RED;
                break;

            case 2:
                mode = GL_RG;
                break;

            case 3:
                mode = GL_RGB;
                break;

            case 4:
                mode = GL_RGBA;
                break;
            }

            // Create Texture
            glTexImage2D(GL_TEXTURE_2D, 0, mode, t.width, t.height, 0, mode, GL_UNSIGNED_BYTE, t.data);

            // Generate MipMap & Set Parameters
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else
        {
            LOG::ERROR("OpenGL", "No Texture Data");
            return "";
        }

        LOG::SYSTEM("OpenGL", "Loaded Texture (%s)", name.c_str());
        textures[name] = std::pair<texture, uint>(t, id);
        return name;
    }

    void OpenGL::draw_texture(std::string name, vec2 center, vec2 size, float rotation)
    {
        // Select 2D Renderer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, windower->width, windower->height);
        glUseProgram(shaders["__default"].second);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[name].second);

        glUniform2f(glGetUniformLocation(shaders["__default"].second, "center"), center.x, center.y);
        glUniform2f(glGetUniformLocation(shaders["__default"].second, "size"), size.x, size.y);
        glUniform2f(glGetUniformLocation(shaders["__default"].second, "ratio"), 1.0f, (float)windower->width / (float)windower->height);
        glUniform1f(glGetUniformLocation(shaders["__default"].second, "rotation"), rotation);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void OpenGL::free_shader(std::string name)
    {
        glDeleteProgram(shaders[name].second);
        shaders.erase(name);
    }

    void OpenGL::free_texture(std::string name)
    {
        free(textures[name].first.data);
        textures.erase(name);
    }
}