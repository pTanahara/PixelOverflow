#pragma once

#include "render/primitive.hpp"
#include "render/framebuffer.hpp"
#include <cstddef>

namespace PixelOverflow {
    class Renderer {
    private:
        FramebufferHDR framebuffer_hdr;
        FramebufferLDR framebuffer_ldr;
        Depthbuffer16 depthbuffer;

        PrimitiveBuffer tri_buffer;
    public:
        Renderer(size_t width, size_t height, size_t num_tiles, size_t reserve_size, size_t reserve_size_per_tile) :
            framebuffer_hdr(width, height),
            framebuffer_ldr(width, height),
            depthbuffer(width, height),
            tri_buffer(num_tiles, reserve_size, reserve_size_per_tile) {}
        // ~Renderer();

        void render_framebuffer();
        FramebufferLDR& get_framebuffer() { return framebuffer_ldr; }

        void add_test_triangle();
    };
}

