#include "render/renderer.hpp"
#include "render/post.hpp"
#include "render/primitive.hpp"
#include "render/raster.hpp"
#include "core/context.hpp"
#include "render/tile.hpp"


using namespace PixelOverflow;

void Renderer::render_framebuffer() {
    TileBoundingBox bb = {Context::get().engine.width, 0, Context::get().engine.height, 0};
    rasterize_triangle(framebuffer_hdr, tri_buffer.pool[0], bb);
    tone_mapping_sse2(framebuffer_hdr, framebuffer_ldr);
}

void Renderer::add_test_triangle() {
    Primitive tri = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1920, 1080, 0, 0, 0, 0, 0, 0},
        {0, 1080, 0, 0, 0, 0, 0, 0}
    };

    tri_buffer.pool[0] = tri;
};

