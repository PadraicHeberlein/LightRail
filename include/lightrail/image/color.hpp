#pragma once

#include <array>
#include <cstdint>
#include "lightrail/math/vec3.hpp"

namespace lightrail {

/**
 * @brief Floating-point RGB color representation.
 * Components r, g, b typically reside in [0.0, 1.0] for standard dynamic range.
 */
struct Color {
    double r{0.0};
    double g{0.0};
    double b{0.0};

    constexpr Color() noexcept = default;
    constexpr Color(double r, double g, double b) noexcept : r(r), g(g), b(b) {}
    constexpr explicit Color(const Vec3& v) noexcept : r(v.x), g(v.y), b(v.z) {}

    Vec3 to_vec3() const;

    Color& operator+=(const Color& c);
    Color& operator*=(double s);
    Color& operator*=(const Color& c);

    /**
     * @brief Converts linear floating-point color to gamma-corrected 8-bit RGB integers in [0, 255].
     * @param gamma_correct When true, applies gamma = 2.0 (square root approximation) for display output.
     * @return std::array<uint8_t, 3> containing {red, green, blue} bytes.
     */
    std::array<uint8_t, 3> to_rgb8(bool gamma_correct = true) const;

    // Palette constants
    static constexpr Color black() noexcept { return Color(0.0, 0.0, 0.0); }
    static constexpr Color white() noexcept { return Color(1.0, 1.0, 1.0); }
    static constexpr Color red() noexcept   { return Color(1.0, 0.0, 0.0); }
    static constexpr Color green() noexcept { return Color(0.0, 1.0, 0.0); }
    static constexpr Color blue() noexcept  { return Color(0.0, 0.0, 1.0); }
};

// Color operations
Color operator+(const Color& c1, const Color& c2);
Color operator*(double s, const Color& c);
Color operator*(const Color& c, double s);
Color operator*(const Color& c1, const Color& c2); // Hadamard modulation

} // namespace lightrail
