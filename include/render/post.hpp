#pragma once

#include "render/framebuffer.hpp"

namespace PixelOverflow {
    void tone_mapping_sse2(FramebufferHDR& framebuffer_hdr, FramebufferLDR& framebuffer_ldr, float exposure = 1.0f);
}

// void raw_mapping(std::vector<Eigen::Vector4f>& framebuffer_hdr, std::vector<uint32_t>& framebuffer);

