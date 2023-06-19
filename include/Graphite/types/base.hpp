#pragma once

#include <string>
#include <vector>

#include <mathutil/vector.hpp>

namespace Graphite {

// GLSL Shader Code
typedef struct {
    std::string vertex, fragment, geometry;
} Shader;

// RAW Texture
typedef struct {
    unsigned char *data;
    int width, height;
    int channels;
} Texture;

// 3D Vertex (Position, TexCoord, Normal)
typedef struct {
    vec3 position;
    vec2 texcoord;
    vec3 normal;
} Vertex;

// 3D Mesh
typedef struct {
    std::vector<Vertex> vertices;

    std::vector<int> indices;
} Mesh;

// Material
typedef struct {

} Material;

// 3D Object
typedef struct {
    std::string group;

    Mesh mesh;
    Material material;
} Object;

}; // namespace Graphite