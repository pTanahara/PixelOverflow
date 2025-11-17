#include "render/raster.hpp"
#include "core/types.hpp"
#include "render/framebuffer.hpp"
#include "render/primitive.hpp"
#include "render/tile.hpp"
#include <algorithm>


using namespace PixelOverflow;

namespace PixelOverflow {
    void rasterize_triangle(
            FramebufferHDR& framebuffer,
            const Primitive& tri,
            TileBoundingBox& bb
            ) {
        PrimitiveVertex v0 = tri.v0, v1 = tri.v1, v2 = tri.v2;

        u32 xmin = std::min({ v0.x, v1.x, v2.x });
        u32 xmax = std::max({ v0.x, v1.x, v2.x });
        u32 ymin = std::min({ v0.y, v1.y, v2.y });
        u32 ymax = std::max({ v0.y, v1.y, v2.y });

        xmin = std::max(xmin, bb.xmin);
        xmax = std::min(xmax, bb.xmax);
        ymin = std::max(ymin, bb.ymin);
        ymax = std::min(ymax, bb.ymax);

        int w0_row = (v2.x - v1.x) * (ymin - v1.y) - (v2.y - v1.y) * (xmin - v1.x);
        int w1_row = (v0.x - v2.x) * (ymin - v2.y) - (v0.y - v2.y) * (xmin - v2.x);
        int w2_row = (v1.x - v0.x) * (ymin - v0.y) - (v1.y - v0.y) * (xmin - v0.x);

        float inv_area = 2.0f / static_cast<float>(w0_row + w1_row + w2_row);

        int A01 = v0.y - v1.y, B01 = v1.x - v0.x;
        int A12 = v1.y - v2.y, B12 = v2.x - v1.x;
        int A20 = v2.y - v0.y, B20 = v0.x - v2.x;

        for (int y = ymin; y < ymax; y++) {
            int w0 = w0_row;
            int w1 = w1_row;
            int w2 = w2_row;

            for (int x = xmin; x < xmax; x++) {
                if ((w0 | w1 | w2) >= 0)
                    draw_pixel(framebuffer, x, y, w0, w1, w2, inv_area);

                w0 += A12;
                w1 += A20;
                w2 += A01;
            }

            w0_row += B12;
            w1_row += B20;
            w2_row += B01;
        }
    }

    void draw_pixel(
            FramebufferHDR& framebuffer,
            int x,
            int y,
            int w0,
            int w1,
            int w2,
            float inv_area
            ) {
        framebuffer.draw_pixel(x, y, 100.0f, 100.0f, 100.0f);
    }
}
