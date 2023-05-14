#include <GameEngine/core/MediaEngine/renderers/OpenGL.h>

namespace GameEngine::MEDIA::RENDERER
{
    OpenGL::OpenGL(std::string name, bool fullscreen, int width, int height)
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
                     "uniform int type;\n"
                     "uniform sampler2D tex;\n"
                     "uniform vec3 color;\n"
                     "uniform float cutradius;\n"
                     "void main()\n"
                     "{\n"
                     "    switch (type)\n"
                     "    {\n"
                     "    case 0:\n"
                     "        // Color\n"
                     "        FragColor = vec4(color.rgb, 1.0);\n"
                     "        break;\n"
                     "    case 1:\n"
                     "        // Texture\n"
                     "        FragColor = texture(tex, TexCoord);\n"
                     "        break;\n"
                     "    case 2:\n"
                     "        // Text\n"
                     "        FragColor = vec4(color.rgb, length(texture(tex, TexCoord).rgb));\n"
                     "        break;\n"
                     "    case 3:\n"
                     "        // Circle\n"
                     "        vec2 val = FragPos;\n"
                     "        float R = 1.0f;\n"
                     "        float R2 = cutradius;\n"
                     "        float dist = sqrt(dot(val, val));\n"
                     "        //if (dist >= R || dist <= R2)\n"
                     "            \n"
                     "        float sm = smoothstep(R, R - 0.01, dist);\n"
                     "        float sm2 = smoothstep(R2, R2 + 0.01, dist);\n"
                     "        float alpha = sm * sm2;\n"
                     "        FragColor = vec4(color.xyz, 1.0);\n"
                     "        break;\n"
                     "    default:\n"
                     "        FragColor = vec4(color.xyz, 0.0);\n"
                     "        break;\n"
                     "    }\n"
                     "}";

        // Failed to Init Shader
        if (add("__builtin_shader_2d", s) == "")
            LOG::ERROR("OpenGL", "Failed to load 2D Shader");
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

    std::string OpenGL::add(std::string name, shader s)
    {
        const char *vertex = s.vertex.c_str();
        const char *fragment = s.fragment.c_str();
        const char *geometry = s.geometry.c_str();

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
        LOG::SYSTEM("OpenGL", "Loaded Texture (%s)", name.c_str());
        textures[name] = std::pair<texture, uint>(t, 0);
        return name;
    }
}