#include <cstddef>
#include <cstdint>
#include <memory>


namespace Memory {
    class GraveyardAllocator {
    private:
        struct BlockHeader {
            size_t size;
            uint32_t id;
            uint32_t generation;
        };

        std::unique_ptr<char[]> arena;
        size_t arena_head, deadzone_head;
        size_t arena_size, deadzone_size;
        uint32_t curr_id = 0;

        std::unique_ptr<BlockHeader[]> blocks;

    public:
        GraveyardAllocator(size_t arena_size, size_t deadzone_size, uint32_t num_headers = 4096);

        void* allocate(size_t size, size_t alignment);
    };

    // TODO FINISH
    struct LinearAllocator {
        std::unique_ptr<std::byte[]> arena = std::make_unique<std::byte[]>(0);
        size_t head = 0;
        size_t capacity = 0;
        static constexpr size_t grow_amount = 16u * 1024u * 1024u; 

        void grow() {

        }
    };

    template<size_t N>
    struct FrameAllocator {
        std::unique_ptr<std::byte[]> arena = std::make_unique<std::byte[]>(N);
        size_t head = 0;
        size_t capacity = N;

        template<typename T>
        T* allocate(size_t size, size_t alignment = alignof(T)) {
            std::byte* current = arena.get() + head;
            size_t free_space = capacity - head;

            void* aligned_ptr = static_cast<void*>(current);
            if (std::align(alignment, sizeof(T), aligned_ptr, free_space)) {
                std::byte* result = static_cast<std::byte*>(aligned_ptr);
                head = (result + size) - arena.get();

                if (head > capacity) [[unlikely]]
                    throw std::bad_alloc();

                return reinterpret_cast<T*>(result);

            } else {
                return nullptr;
            }
        }

        void reset() {
            head = 0;
        }
    };
}
