#include "lightrail/image/color.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace lightrail {

Vec3 Color::to_vec3() const {
    return Vec3(r, g, b);
}

Color& Color::operator+=(const Color& c) {
    // TODO: Implement color in-place addition
    throw std::logic_error("Not implemented: Color::operator+=");
}

Color& Color::operator*=(double s) {
    // TODO: Implement color in-place scalar multiplication
    throw std::logic_error("Not implemented: Color::operator*=(double)");
}

Color& Color::operator*=(const Color& c) {
    // TODO: Implement color in-place component modulation
    throw std::logic_error("Not implemented: Color::operator*=(Color)");
}

std::array<uint8_t, 3> Color::to_rgb8(bool gamma_correct) const {
    // TODO: Implement conversion from linear RGB to 8-bit unsigned integer RGB [0, 255]
    // 1. Check for NaNs and replace with 0.0
    // 2. If gamma_correct is true, apply gamma = 2.0 via sqrt(channel)
    // 3. Clamp channel value to [0.0, 0.999]
    // 4. Scale to integer: static_cast<uint8_t>(256.0 * clamped)
    throw std::logic_error("Not implemented: Color::to_rgb8()");
}

Color operator+(const Color& c1, const Color& c2) {
    // TODO: Implement color addition: Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b)
    throw std::logic_error("Not implemented: operator+(Color, Color)");
}

Color operator*(double s, const Color& c) {
    // TODO: Implement scalar * color
    throw std::logic_error("Not implemented: operator*(double, Color)");
}

Color operator*(const Color& c, double s) {
    return s * c;
}

Color operator*(const Color& c1, const Color& c2) {
    // TODO: Implement color modulation: Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b)
    throw std::logic_error("Not implemented: operator*(Color, Color)");
}

} // namespace lightrail
