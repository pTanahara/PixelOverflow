#include "render/post.hpp"
#include "core/types.hpp"
#include <algorithm>
#include <cstdint>
#include <emmintrin.h>
#include <smmintrin.h>
#include <tmmintrin.h>
#include <xmmintrin.h>
#include <SDL3/SDL_endian.h>

using namespace PixelOverflow;

inline uint32_t float_to_rgba8(float r, float g, float b) {
    uint8_t ur = static_cast<uint8_t>(std::clamp(r, 0.0f, 1.0f) * 255.0f);
    uint8_t ug = static_cast<uint8_t>(std::clamp(g, 0.0f, 1.0f) * 255.0f);
    uint8_t ub = static_cast<uint8_t>(std::clamp(b, 0.0f, 1.0f) * 255.0f);

    return (ur << 24) | (ug << 16) | (ub << 8) | 255;
}

namespace PixelOverflow {
    void tone_mapping_sse2(FramebufferHDR& framebuffer_hdr, FramebufferLDR& framebuffer_ldr, float exposure) {
        u32 size = framebuffer_hdr.width * framebuffer_hdr.height;

        const __m128 exposure_v = _mm_set1_ps(exposure);
        const __m128 ONE = _mm_set1_ps(1.0f);
        const __m128 TFF = _mm_set1_ps(255.0f);
        const __m128i A32 = _mm_set1_epi32(0x000000FF);

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
        const __m128i RGBA_SHUFFLE_MASK = _mm_setr_epi8(
            12, 8, 4, 0,
            13, 9, 5, 1,
            14, 10, 6, 2,
            15, 11, 7, 3
        );
#else
        const __m128i RGBA_SHUFFLE_MASK = _mm_setr_epi8(
            0, 4, 8, 12,
            1, 5, 9, 13,
            2, 6, 10, 14,
            3, 7, 11, 15
        );
#endif

        int i = 0;
        for (; i <= size - 4; i += 4) {
            __m128 r = _mm_loadu_ps(&framebuffer_hdr.r[i]);
            __m128 g = _mm_loadu_ps(&framebuffer_hdr.g[i]);
            __m128 b = _mm_loadu_ps(&framebuffer_hdr.b[i]);

            r = _mm_mul_ps(r, exposure_v);
            g = _mm_mul_ps(g, exposure_v);
            b = _mm_mul_ps(b, exposure_v);

            // Reinhard tone mapping
            r = _mm_mul_ps(r, _mm_rcp_ps(_mm_add_ps(r, ONE)));
            g = _mm_mul_ps(g, _mm_rcp_ps(_mm_add_ps(g, ONE)));
            b = _mm_mul_ps(b, _mm_rcp_ps(_mm_add_ps(b, ONE)));

            r = _mm_mul_ps(r, TFF);
            g = _mm_mul_ps(g, TFF);
            b = _mm_mul_ps(b, TFF);

            __m128i R32 = _mm_cvtps_epi32(r);
            __m128i G32 = _mm_cvtps_epi32(g);
            __m128i B32 = _mm_cvtps_epi32(b);

            __m128i RG16 = _mm_packus_epi32(R32, G32);
            __m128i BA16 = _mm_packus_epi32(B32, A32);

            __m128i RGBA8 = _mm_packus_epi16(RG16, BA16);

            __m128i RGBA = _mm_shuffle_epi8(RGBA8, RGBA_SHUFFLE_MASK);

            _mm_storeu_si128((__m128i*)&framebuffer_ldr.pixels[i], RGBA);
        }
    }
}


