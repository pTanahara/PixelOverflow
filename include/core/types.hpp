#pragma once

#include "mimalloc.h"
#include <atomic>
#include <cstdint>


using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;

using f64 = double;
using f32 = float;

namespace PixelOverflow {
    template<typename T, size_t SIZE, size_t ALIGNMENT>
    struct AtomicArray {
        T* array;
        std::atomic<size_t> p = 0;

        AtomicArray() {
            array = static_cast<T*>(mi_malloc_aligned(SIZE * sizeof(T), ALIGNMENT));
        }

        ~AtomicArray() {
            mi_free(array);
        }

        void insert(const T& elem) {
            size_t i = p.fetch_add(1, std::memory_order_relaxed);
            i = i % SIZE;

            array[i] = elem;
        }

        void clear() {
            p.store(0, std::memory_order_relaxed);
        }
    };
}
