#pragma once

#include <reactphysics3d/mathematics/mathematics.h>

#include <string>

namespace GameEngine
{
    typedef reactphysics3d::Vector2 vec2;
    typedef reactphysics3d::Vector3 vec3;

    typedef reactphysics3d::Matrix2x2 mat2;
    typedef reactphysics3d::Matrix3x3 mat3;

    typedef reactphysics3d::Quaternion Quaternion;
    typedef reactphysics3d::Transform Transform;
    typedef reactphysics3d::Ray Ray;

    struct texture
    {
        int width, height, nrChannels;
        unsigned char *data = nullptr;
    };

    struct shader
    {
        std::string vertex;
        std::string fragment;
        std::string geometry;
    };

    struct material
    {
        texture diffuse;
        texture specular;

        float shininess = 32.0f;

        bool lit = true;

        // TODO: Emission Map, Transparencity Map
    };

    struct mesh
    {
        std::vector<vec3> vertices;
        std::vector<vec3> normals;
        std::vector<vec2> texcoords;

        std::string material;
    };
}