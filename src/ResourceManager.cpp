#include <Graphite/core/ResourceManager.h>

#include <GL/glad.h>
#include <GL/stb_image.h>

#include <cstring>
#include <fstream>
#include <random>

namespace Graphite {

ResourceManager::ResourceManager(std::string shaderPath,
                                 std::string texturePath,
                                 std::string materialPath, std::string meshPath)
    : defaultPath{shaderPath, texturePath, materialPath, meshPath} {
    // TODO: Init Resource Loader
}

ResourceManager::ResourceManager(std::string resourcePath)
    : ResourceManager(resourcePath + "shaders/", resourcePath + "textures/",
                      resourcePath + "materials/", resourcePath + "meshes/") {}

ResourceManager::~ResourceManager() {
    // Free Textures
    for (Texture tex : textures)
        free(tex.data);

    textures.clear();

    // Free Materials
    // for (Material mat : materials)

    materials.clear();

    // Free Meshes
    for (Mesh mesh : meshes) {
        mesh.vertices.clear();
        mesh.texcoords.clear();
        mesh.normals.clear();

        mesh.faces.clear();
    }

    meshes.clear();
}

unsigned int ResourceManager::load_shader(std::string path) {
    Shader out;

    uint shader_type = 0;

    std::ifstream file(defaultPath[0] + path);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            char buf[10];
            sscanf(line.c_str(), "%9s", buf);

            if (!strcmp(buf, "#vertex"))
                shader_type = 1;
            else if (!strcmp(buf, "#geometry"))
                shader_type = 2;
            else if (!strcmp(buf, "#fragment"))
                shader_type = 3;
            else
                switch (shader_type) {
                case 1:
                    out.vertex += line + "\n";
                    break;

                case 2:
                    out.geometry += line + "\n";
                    break;

                case 3:
                    out.fragment += line + "\n";
                    break;

                default:
                    break;
                }
        }

        file.close();
    }

    shaders.push_back(out);
    // TODO: Fix
    return shaders.size();
}

unsigned int ResourceManager::load_texture(std::string path) {
    Texture out;

    out.data = stbi_load((defaultPath[1] + path).c_str(), &out.width,
                         &out.height, &out.channels, 0);

    if (out.data == nullptr)
        return 0;

    textures.push_back(out);
    return textures.size();
}

std::vector<std::string> ResourceManager::load_material(std::string path) {
    std::vector<std::string> out;

    std::ifstream file(defaultPath[2] + path);
    if (file.is_open()) {
        std::string cursor;
        Material *p;

        std::string line;
        while (getline(file, line)) {
            char index[8];
            char data[129];

            sscanf(line.c_str(), "%7s %128s", index, data);

            if (!strcmp(index, "newmtl")) {
                // New Material
                cursor = data;
                p = &mtl[path][cursor];
            } else {
                // DoSomething
            }
        }

        file.close();
    }

    return out;
}

std::vector<std::string> ResourceManager::load_mesh(std::string path) {
    std::vector<std::string> out;

    // TODO
    std::ifstream file(defaultPath[3] + path);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            char index[8];
            char data[129];

            sscanf(line.c_str(), "%7s %128s", index, data);

            if (!strcmp(index, "o")) {
                // New Object
            } else {
                // DoSomething
            }
        }

        file.close();
    }

    return out;
}

} // namespace Graphite
