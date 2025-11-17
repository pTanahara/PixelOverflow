
namespace PixelOverflow {
    struct Vec3 {
        float x, y, z;
    };

    struct Vec4 {
        float x, y, z, w;
    };

    struct Mat4 {
        float m[16];

        float& operator[](int i) { return m[i]; }
        const float& operator[](int i) const { return m[i]; }
    };
}
