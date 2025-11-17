#pragma once

#include <cstdint>


namespace PixelOverflow {
    struct TileBoundingBox {
        uint32_t xmax, xmin;
        uint32_t ymax, ymin;
    };
}
