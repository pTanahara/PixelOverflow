#pragma once

#include "core/types.hpp"
#include <cstdint>
#include <vector>


namespace PixelOverflow {
    struct PrimitiveVertex {
        u16 x, y, z;
        u16 n0, n1, n2;
        u16 u, v;
    };

    struct Primitive {
        PrimitiveVertex v0, v1, v2;
    };

    struct PrimitivePool {
        std::vector<Primitive> tri;

        void reserve_all(size_t RESERVE_SIZE) {
            tri.reserve(RESERVE_SIZE);
        }

        void clear_all() {
            tri.clear();
        }

        Primitive& operator[](int i) { return tri[i]; }
        const Primitive& operator[](int i) const { return tri[i]; }
    };

    struct PrimitiveList {
        std::vector<uint32_t> tri_index;

        void reserve_all(size_t RESERVE_SIZE_PER_TILE) {
            tri_index.reserve(RESERVE_SIZE_PER_TILE);
        }

        void clear_all() {
            tri_index.clear();
        }

        uint32_t& operator[](int i) { return tri_index[i]; }
        const uint32_t& operator[](int i) const { return tri_index[i]; }
    };

    struct PrimitiveBuffer {
        PrimitivePool pool;
        std::vector<PrimitiveList> opaque;
        std::vector<PrimitiveList> transparent;

        size_t RESERVE_SIZE;
        size_t RESERVE_SIZE_PER_TILE;

        PrimitiveBuffer(size_t NUM_TILES, size_t RESERVE_SIZE, size_t RESERVE_SIZE_PER_TILE) {
            this->RESERVE_SIZE = RESERVE_SIZE;
            this->RESERVE_SIZE_PER_TILE = RESERVE_SIZE_PER_TILE;

            resize_num_tiles(NUM_TILES);
        }

        void resize_num_tiles(size_t NUM_TILES) {
            pool.reserve_all(RESERVE_SIZE);

            opaque.resize(NUM_TILES);
            for (PrimitiveList& t : opaque) {
                t.reserve_all(RESERVE_SIZE_PER_TILE);
            }

            transparent.resize(NUM_TILES);
            for (PrimitiveList& t : transparent) {
                t.reserve_all(RESERVE_SIZE_PER_TILE);
            }
        }

        void clear_all() {
            pool.clear_all();
            
            for (PrimitiveList& t : opaque) {
                t.clear_all();
            }

            for (PrimitiveList& t : transparent) {
                t.clear_all();
            }
        }
    };
}

