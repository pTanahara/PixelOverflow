#pragma once

#include "core/types.hpp"
#include <string>

namespace PixelOverflow {
    struct EngineContext {
        std::string title = "PixelOverflow";
        u32 framerate = 60;
        u32 width = 1920 / 2;
        u32 height = 1080 / 2;
        bool fullscreen = false;

        f32 exposure = 1.0f;

    };

    struct RenderContext {
        // Tile pixels must follow morton order
        const u32 tile_x = 16; // Number of pixels per tile in the horizontal
        const u32 tile_y = 16; // Number of pixels per tile in the vertical
        const u32 tile_group_x = 8; // Number of tiles per tile group in the horizontal
        const u32 tile_group_y = 8; // Number of tiles per tile group in the vertical

        u32 primitive_reserve_size = (1 << 18); // Number of triangles to reserve in the PrimitiveBuffer
        u32 primitive_reserve_size_per_tile_opaque = (primitive_reserve_size / 1024);
        u32 primitive_reserve_size_per_tile_transparent = (primitive_reserve_size / 8192);
    };

    struct DebugContext {
        
    };

    class Context {
    private:
        Context() = default;

    public:
        static Context& get() {
            static Context ctx;
            return ctx;
        }
 
        EngineContext engine;
        RenderContext render; 
    };
}
