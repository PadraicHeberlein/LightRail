#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include "lightrail/math/vec3.hpp"

namespace lightrail {

// Color represented as floating point (R, G, B) components, typically in [0.0, 1.0]
struct Color {
    double r{0.0};
    double g{0.0};
    double b{0.0};

    constexpr Color() noexcept = default;
    constexpr Color(double r, double g, double b) noexcept : r(r), g(g), b(b) {}
    constexpr explicit Color(const Vec3& v) noexcept : r(v.x), g(v.y), b(v.z) {}

    constexpr Vec3 to_vec3() const noexcept {
        return Vec3(r, g, b);
    }

    constexpr Color& operator+=(const Color& c) noexcept {
        r += c.r;
        g += c.g;
        b += c.b;
        return *this;
    }

    constexpr Color& operator*=(double s) noexcept {
        r *= s;
        g *= s;
        b *= s;
        return *this;
    }

    constexpr Color& operator*=(const Color& c) noexcept {
        r *= c.r;
        g *= c.g;
        b *= c.b;
        return *this;
    }

    // Convert linear color to gamma-corrected 8-bit RGB [0, 255]
    // Uses standard gamma = 2.0 (square root approximation) for realistic brightness
    std::array<uint8_t, 3> to_rgb8(bool gamma_correct = true) const noexcept {
        double red   = r;
        double green = g;
        double blue  = b;

        // Replace NaNs with zero
        if (std::isnan(red))   red   = 0.0;
        if (std::isnan(green)) green = 0.0;
        if (std::isnan(blue))  blue  = 0.0;

        if (gamma_correct) {
            red   = (red > 0.0)   ? std::sqrt(red)   : 0.0;
            green = (green > 0.0) ? std::sqrt(green) : 0.0;
            blue  = (blue > 0.0)  ? std::sqrt(blue)  : 0.0;
        }

        // Clamp to [0.0, 0.999] and scale to [0, 255]
        auto to_byte = [](double val) noexcept -> uint8_t {
            double clamped = std::clamp(val, 0.0, 0.999);
            return static_cast<uint8_t>(256.0 * clamped);
        };

        return {to_byte(red), to_byte(green), to_byte(blue)};
    }

    // Preset palette colors
    static constexpr Color black() noexcept { return Color(0.0, 0.0, 0.0); }
    static constexpr Color white() noexcept { return Color(1.0, 1.0, 1.0); }
    static constexpr Color red()   noexcept { return Color(1.0, 0.0, 0.0); }
    static constexpr Color green() noexcept { return Color(0.0, 1.0, 0.0); }
    static constexpr Color blue()  noexcept { return Color(0.0, 0.0, 1.0); }
};

constexpr Color operator+(const Color& c1, const Color& c2) noexcept {
    return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
}

constexpr Color operator-(const Color& c1, const Color& c2) noexcept {
    return Color(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b);
}

constexpr Color operator*(const Color& c1, const Color& c2) noexcept {
    return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
}

constexpr Color operator*(double s, const Color& c) noexcept {
    return Color(s * c.r, s * c.g, s * c.b);
}

constexpr Color operator*(const Color& c, double s) noexcept {
    return s * c;
}

} // namespace lightrail
