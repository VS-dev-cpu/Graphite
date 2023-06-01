#pragma once

#include <reactphysics3d/mathematics/mathematics.h>

#include <string>
#include <vector>

namespace Graphite {

// React Physics Typenames
typedef reactphysics3d::Vector2 vec2;
typedef reactphysics3d::Vector3 vec3;

typedef reactphysics3d::Matrix2x2 mat2;
typedef reactphysics3d::Matrix3x3 mat3;

typedef reactphysics3d::Quaternion Quaternion;
typedef reactphysics3d::Transform Transform;
typedef reactphysics3d::Ray Ray;

// RAW Texture
typedef struct {
    unsigned char *data;
    int width, height;
    int channels;
} Texture;

// Material
typedef struct {
    Texture diffuse;
    Texture specular;

    float shininess;

    bool lit;

    // TODO: Emission Map, Transparencity Map
} Material;

// Mesh
typedef struct {
    std::vector<float> vertices, texcoords, normals;
    std::vector<int> faces;

    std::string material_name;
    unsigned int material;
} Mesh;

} // namespace Graphite