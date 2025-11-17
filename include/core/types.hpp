#pragma once

#include "mimalloc.h"
#include <atomic>
#include <cassert>
#include <cstddef>
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
    // SIZE must be multiple of 2
    template<typename T, size_t ALIGNMENT = alignof(T)>
    class AtomicBuffer {
    private:
        T* array;
        std::atomic<size_t> p = 0;
        size_t size;

    public:
        AtomicBuffer(size_t SIZE) {
            assert((SIZE & (SIZE - 1)) == 0 && "SIZE must be a power of 2!");
            size = SIZE;
            array = static_cast<T*>(mi_malloc_aligned(SIZE * sizeof(T), ALIGNMENT));
        }

        ~AtomicBuffer() {
            mi_free(array);
        }

        void insert(const T& elem) {
            size_t i = p.fetch_add(1, std::memory_order_relaxed);
            i = i & (size - 1); // Circular Buffer, multithread unsafe specially for smaller SIZE

            array[i] = elem;
        }

        void clear() {
            p.store(0, std::memory_order_relaxed);
        }

        size_t length() const {
            return p.load(std::memory_order_relaxed);
        }

        const T& get(size_t i) const {
            return array[i & (size - 1)];
        }

        f32 capacity() const {
            return (f32)length() / size;
        }

        const T& operator[](size_t i) const { return array[i & (size - 1)]; }
    };
}
