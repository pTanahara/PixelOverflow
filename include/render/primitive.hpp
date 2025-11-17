#pragma once

#include "core/types.hpp"
#include "mimalloc.h"


namespace PixelOverflow {
    struct PrimitiveVertex {
        u16 x, y, z;
        u16 n0, n1, n2;
        u16 u, v;
    };

    struct Primitive {
        PrimitiveVertex v0, v1, v2;
    };

    struct PrimitivePool : public AtomicBuffer<Primitive> {};

    struct PrimitiveList : public AtomicBuffer<u32> {};

    struct PrimitiveBuffer {
        PrimitivePool pool;
        PrimitiveList* opaque;
        PrimitiveList* transparent;
        size_t num_tiles;

        PrimitiveBuffer(size_t NUM_TILES, size_t RESERVE_SIZE, size_t RESERVE_SIZE_PER_TILE_OPAQUE, size_t RESERVE_SIZE_PER_TILE_TRANSPARENT) : pool(RESERVE_SIZE), num_tiles(NUM_TILES) {
            opaque = static_cast<PrimitiveList*>(mi_malloc(NUM_TILES * sizeof(PrimitiveList)));
            transparent = static_cast<PrimitiveList*>(mi_malloc(NUM_TILES * sizeof(PrimitiveList)));

            for (size_t i = 0; i < NUM_TILES; i++) {
                new(&opaque[i]) PrimitiveList(RESERVE_SIZE_PER_TILE_OPAQUE);
                new(&transparent[i]) PrimitiveList(RESERVE_SIZE_PER_TILE_TRANSPARENT);
            }
        }

        ~PrimitiveBuffer() {
            for (size_t i = 0; i < num_tiles; ++i) {
                opaque[i].~PrimitiveList();
                transparent[i].~PrimitiveList();
            }

            mi_free(opaque);
            mi_free(transparent);
        }

        void clear_all() {
            pool.clear();

            for (size_t i = 0; i < num_tiles; i++) {
                opaque[i].clear();
            }

            for (size_t i = 0; i < num_tiles; i++) {
                transparent[i].clear();
            }
        }
    };
}

