#pragma once

#include <string>
#include <unordered_map>
#include <vector>

typedef struct {
    unsigned char *data;
    int width, height;
    int channels;
} Texture;

typedef struct {
} Material;

typedef struct {
    std::vector<float> vertices, texcoords, normals;
    std::vector<int> faces;
} Mesh;

namespace Graphite {

// Resource Loader & Manager
class ResourceManager {
  public:
    ResourceManager();
    ~ResourceManager();

    // Load Texture(s) from file (returns: number of textures loaded)
    unsigned int load_texture(std::string path);

    // Load Material(s) from file (returns: number of materials loaded)
    unsigned int load_material(std::string path);

    // Load Material(s) from file (returns: number of meshes loaded)
    unsigned int load_mesh(std::string path);

  private:
    std::vector<Texture> textures;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;

    // .obj and .mtl files use strings to identify objects/materials
    // but we use numbers (unsigned integers) to index them
    // these variables stores the names associated with the indexes
    // only for loading !!! using them may reduce performance
    std::unordered_map<std::string, unsigned int> material_lookup;
    std::unordered_map<std::string, unsigned int> mesh_lookup;
};

// Load Texture
Texture texture(std::string path);

// Load Material
std::vector<Material> material(std::string path);

// Load Mesh
Mesh mesh(std::string path);

} // namespace Graphite
