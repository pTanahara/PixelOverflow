#pragma once

#include "scene/mesh.hpp"

namespace Scene {
    enum ObjectType {
        NONE,
        MESH,
        LIGHT,
        CAMERA
    };

    struct Object {
        ObjectType type = NONE;
        union {
            Mesh mesh;
            Light light;
            Camera camera;
        } content;
    };


}
