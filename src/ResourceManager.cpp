#include <Graphite/core/ResourceManager.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Graphite/core/stb_image.h>

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

    mtl.clear();

    // Free Meshes
    // for (auto [name, mesh] : obj) {
    //     mesh.vertices.clear();
    //     mesh.texcoords.clear();
    //     mesh.normals.clear();
    // }

    obj.clear();
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

        std::string line;
        while (getline(file, line)) {
            char index[8];
            char data[129];

            sscanf(line.c_str(), "%7s %128s", index, data);

            if (!strcmp(index, "newmtl")) {
                // New Material
                cursor = data;
                out.push_back(cursor);
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

    std::ifstream file(defaultPath[3] + path);

    if (file.is_open()) {
        std::string cursor;

        std::vector<float> vertices, texcoords, normals;

        std::string line;
        while (getline(file, line)) {
            char index[8];
            char data[129];

            sscanf(line.c_str(), "%7s %128s", index, data);

            if (!strcmp(index, "o")) {
                // New Object
                cursor = data;
                out.push_back(cursor);
            } else if (!strcmp(index, "v")) {
                // Vertex (x, y, z, [w])
                float x, y, z, w = 1.0f;
                sscanf(data, "%f %f %f %f", &x, &y, &z, &w);

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(w);
            } else if (!strcmp(index, "vt")) {
                // Vertex Texture (u, v, [w])
                float u, v = 0.0f, w = 0.0f;
                sscanf(data, "%f %f %f", &u, &v, &w);

                texcoords.push_back(u);
                texcoords.push_back(v);
                texcoords.push_back(w);
            } else if (!strcmp(index, "vn")) {
                // Vertex Normal (x, y, z)
                float x, y, z;
                sscanf(data, "%f %f %f", &x, &y, &z);

                normals.push_back(x);
                normals.push_back(y);
                normals.push_back(z);
            } else if (!strcmp(index, "f")) {
                // Face (v[/vt/vn] v[/vt/vn] v[/vt/vn] ...)

                float v[4], t[4], n[4];
                char part[4][128];
                int parts = sscanf(data, "%s %s %s %s", part[0], part[1],
                                   part[2], part[3]);

                for (int i = 0; i < parts; i++) {
                    if (sscanf(part[i], "%f/%f/%f", &v[i], &t[i], &n[i]) != 3)
                        if (sscanf(data, "%f//%f", &v[i], &n[i]) != 2)
                            if (sscanf(data, "%f/%f", &v[i], &t[i]) != 2)
                                if (sscanf(data, "%f", &v[i]) != 1) {
                                    printf("Failed to read Face Line\n");
                                    parts = 0;
                                }
                }

                // for (int i = 0; i < parts; i++) {
                //     for (int j = 0; j < 3; j++) {
                //         obj[cursor].vertices.push_back(vertices[v[i] + j]);
                //         obj[cursor].normals.push_back(normals[n[i] + j]);
                //         if (j < 3)
                //             obj[cursor].texcoords.push_back(
                //                 texcoords[t[i] + j]);
                //     }
                // }

            } else {
                // TODO: Something
            }
        }

        file.close();
    }

    return out;
}

} // namespace Graphite
