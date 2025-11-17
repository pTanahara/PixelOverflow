#pragma once

#include "render/framebuffer.hpp"
#include "render/primitive.hpp"
#include "render/tile.hpp"

namespace PixelOverflow {
    // Based on Fabian "ryg" Giesen implementation of barycentric coordinate rasterizer
    // https://fgiesen.wordpress.com/2013/02/10/optimizing-the-basic-rasterizer/
    void rasterize_triangle(
            FramebufferHDR& framebuffer,
            const Primitive& tri,
            TileBoundingBox& bb
    );

    void draw_pixel(
            FramebufferHDR& framebuffer,
            int x,
            int y,
            int w0,
            int w1,
            int w2,
            float inv_area
    );
}

