#pragma once

#include "scene/bounding_box.hpp"
#include "scene/object.hpp"
#include <vector>

namespace Scene {
    struct NodeTransform {
        Eigen::Matrix4f world;
        Eigen::Matrix4f local;
    };

    struct Node {
        Node* parent = nullptr;
        NodeTransform* transform = nullptr;
        Object* object = nullptr;

        AABB bounding_box;

        Node* children[2] = { nullptr, nullptr };
    };

    struct Scene {
        std::vector<Node*> static_nodes;
        std::vector<Node*> dynamic_nodes;
    };
}
