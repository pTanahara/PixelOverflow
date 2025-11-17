#pragma once

#include <cstdint>
#include <vector>


namespace PixelOverflow {
    struct FramebufferHDR {
        uint32_t width;
        uint32_t height;

        std::vector<float> r;
        std::vector<float> g;
        std::vector<float> b;

        void resize(uint32_t w, uint32_t h) {
            width = w;
            height = h;

            r.resize(w * h, 0.0f);
            g.resize(w * h, 0.0f);
            b.resize(w * h, 0.0f);
        }

        FramebufferHDR(uint32_t w, uint32_t h) {
            resize(w, h);
        }

        void draw_pixel(size_t x, size_t y, float r, float g, float b) {
            size_t n = y * width + x;
            this->r[n] = r;
            this->g[n] = g;
            this->b[n] = b;
        }
    };

    struct FramebufferLDR {
        uint32_t width;
        uint32_t height;

        std::vector<uint32_t> pixels;

        uint32_t& operator[](int i) { return pixels[i]; }
        const uint32_t& operator[](int i) const { return pixels[i]; }

        void resize(uint32_t w, uint32_t h) {
            width = w;
            height = h;

            pixels.resize(w * h, 0x000000FF);
        }

        FramebufferLDR(uint32_t w, uint32_t h) {
            resize(w, h);
        }
    };

    struct Depthbuffer16 {
        uint32_t width;
        uint32_t height;

        std::vector<uint16_t> z;

        uint16_t& operator[](int i) { return z[i]; }
        const uint16_t& operator[](int i) const { return z[i]; }

        void resize(uint32_t w, uint32_t h) {
            width = w;
            height = h;

            z.resize(w * h, 0xFFFF);
        }

        Depthbuffer16(uint32_t w, uint32_t h) {
            resize(w, h);
        }

        void set(uint16_t val = 0xFFFF) {
            std::fill(z.begin(), z.end(), val);
        }
    };
}

