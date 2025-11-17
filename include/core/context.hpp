#pragma once

#include <cstdint>
#include <string>

namespace PixelOverflow {
    struct EngineContext {
        std::string title = "PixelOverflow";
        uint32_t framerate = 60;
        uint32_t width = 1920 / 2;
        uint32_t height = 1080 / 2;
        bool fullscreen = false;

        float exposure = 1.0f;

    };

    struct RenderContext {
        // Tile pixels must follow morton order
        const int tile_x = 16; // Number of pixels per tile in the horizontal
        const int tile_y = 16; // Number of pixels per tile in the vertical
        const int tile_group_x = 8; // Number of tiles per tile group in the horizontal
        const int tile_group_y = 8; // Number of tiles per tile group in the vertical

        int primitive_reserve_size = 4096; // Number of triangles to reserve in the PrimitiveBuffer
        int primitive_reserve_size_per_tile = (int)(primitive_reserve_size / 1024);
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
