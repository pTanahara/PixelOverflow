#pragma once

#include <vector>
#include <cstdint>

#include "material.hpp"
#include "scene/bounding_box.hpp"
#include "skeleton.hpp"

namespace Scene {
    struct Vertex {
        int16_t x, y, z;
        uint16_t padding; // TODO think on something to put here...
    };

    struct VertexNormal {
        int16_t nx, ny;
    };

    struct VertexTex {
        uint16_t u, v;
    };

    struct VertexBones {
        uint8_t bone_id[4];
        uint8_t weights[4];
    };

    struct Mesh {
        std::vector<uint16_t> vertex_id;
        std::vector<uint16_t> vertex_normal_id;
        std::vector<Vertex> vertices;
        std::vector<VertexNormal> normals;
        std::vector<VertexTex> uvs;
        std::vector<VertexBones> bones;
        std::vector<uint16_t> material_id;
        std::vector<Material> materials;

        AABB bounding_box;
        Skeleton skeleton;
    };


}

