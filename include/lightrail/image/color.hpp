/**
 * @file color.hpp
 * @brief Linear floating-point RGB color representation and gamma-corrected 8-bit display conversion.
 * @see [Gamma Correction (Wikipedia)](https://en.wikipedia.org/wiki/Gamma_correction)
 * @see [Ray Tracing in One Weekend: Using Gamma Correction for Accurate Color Intensity](https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials/usinggammacorrectionforaccuratecolorintensity)
 */
#pragma once

#include <array>
#include <cstdint>
#include "lightrail/math/vec3.hpp"

namespace lightrail {

/**
 * @brief Floating-point linear RGB color representation.
 *
 * Components `r`, `g`, `b` typically reside in @f$ [0.0, 1.0] @f$ for standard dynamic range (SDR).
 * Arithmetic is performed in linear light space prior to display gamma encoding.
 *
 * @see [sRGB and Linear Color Space (Wikipedia)](https://en.wikipedia.org/wiki/SRGB)
 */
struct Color {
    double r{0.0};
    double g{0.0};
    double b{0.0};

    constexpr Color() noexcept = default;
    constexpr Color(double r, double g, double b) noexcept : r(r), g(g), b(b) {}
    constexpr explicit Color(const Vec3& v) noexcept : r(v.x), g(v.y), b(v.z) {}

    [[nodiscard]] Vec3 to_vec3() const;

    constexpr bool operator==(const Color&) const noexcept = default;

    Color& operator+=(const Color& c);
    Color& operator*=(double s);
    Color& operator*=(const Color& c);

    /**
     * @brief Converts linear floating-point color to gamma-corrected 8-bit RGB integers in @f$ [0, 255] @f$.
     * @param gamma_correct When true, applies @f$ c^{1/2} = \sqrt{c} @f$ (@f$ \gamma = 2.0 @f$ approximation) for display output.
     * @return `std::array<uint8_t, 3>` containing `{red, green, blue}` bytes.
     * @see [Gamma Correction (Wikipedia)](https://en.wikipedia.org/wiki/Gamma_correction)
     * @see [Ray Tracing in One Weekend: Gamma Correction](https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials/usinggammacorrectionforaccuratecolorintensity)
     */
    [[nodiscard]] std::array<uint8_t, 3> to_rgb8(bool gamma_correct = true) const;

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

/**
 * @brief Component-wise (Hadamard) color modulation @f$ (r_1 r_2, g_1 g_2, b_1 b_2) @f$, modeling spectral surface reflectance.
 */
Color operator*(const Color& c1, const Color& c2);

} // namespace lightrail
