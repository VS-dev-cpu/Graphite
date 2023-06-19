#pragma once

#include <Graphite/types/base.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace Graphite {

// Resource Loader & Manager
class ResourceManager {
  public:
    // Initialize Resource Manager
    ResourceManager(std::string shaderPath, std::string texturePath,
                    std::string materialPath, std::string meshPath);
    ResourceManager(std::string resourcePath = "");

    ~ResourceManager();

    // Load (GLSL) Shader
    unsigned int load_shader(std::string path);

    // Load Texture(s)
    unsigned int load_texture(std::string path);

    // Load Material(s) (returns: list of materials loaded)
    std::vector<std::string> load_material(std::string path);

    // Load Material(s) (returns: list of meshes loaded)
    std::vector<std::string> load_mesh(std::string path);

  private:
    // shader, texture, material, mesh path
    std::string defaultPath[4];

    std::vector<Shader> shaders;
    std::vector<Texture> textures;

    // [.obj] & [.mtl] file containers
    std::unordered_map<std::string, Mesh> obj;
    std::unordered_map<std::string, Material> mtl;
};

// Load Texture
Texture texture(std::string path);

// Load Material
std::vector<Material> material(std::string path);

// Load Mesh
Mesh mesh(std::string path);

} // namespace Graphite
