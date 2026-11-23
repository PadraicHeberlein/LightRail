#pragma once

#include <iosfwd>
#include "lightrail/math/constants.hpp"

namespace lightrail {

/**
 * @brief 3D Vector representation for geometric and physical calculations.
 */
struct Vec3 {
    double x{0.0};
    double y{0.0};
    double z{0.0};

    // Constructors
    constexpr Vec3() noexcept = default;
    constexpr Vec3(double x, double y, double z) noexcept : x(x), y(y), z(z) {}

    // Static factories
    static constexpr Vec3 zero() noexcept { return Vec3(0.0, 0.0, 0.0); }
    static constexpr Vec3 unit_x() noexcept { return Vec3(1.0, 0.0, 0.0); }
    static constexpr Vec3 unit_y() noexcept { return Vec3(0.0, 1.0, 0.0); }
    static constexpr Vec3 unit_z() noexcept { return Vec3(0.0, 0.0, 1.0); }

    // Magnitude & normalization methods
    [[nodiscard]] double length() const;
    [[nodiscard]] double length_squared() const;
    [[nodiscard]] bool approx_equal(const Vec3& other, double epsilon = kEpsilon) const;

    constexpr bool operator==(const Vec3&) const noexcept = default;

    // Compound assignment operators
    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(double s);
    Vec3& operator/=(double s);

    // Unary negation
    [[nodiscard]] Vec3 operator-() const;
};

// Aliases
using Point3 = Vec3;

// Vector arithmetic operators
[[nodiscard]] Vec3 operator+(const Vec3& a, const Vec3& b);
[[nodiscard]] Vec3 operator-(const Vec3& a, const Vec3& b);
[[nodiscard]] Vec3 operator*(const Vec3& a, const Vec3& b); // Component-wise (Hadamard) product
[[nodiscard]] Vec3 operator*(double s, const Vec3& v);
[[nodiscard]] Vec3 operator*(const Vec3& v, double s);
[[nodiscard]] Vec3 operator/(const Vec3& v, double s);

// Vector products & operations
[[nodiscard]] double dot(const Vec3& a, const Vec3& b);
[[nodiscard]] Vec3 cross(const Vec3& a, const Vec3& b);
[[nodiscard]] Vec3 unit_vector(const Vec3& v);

[[nodiscard]] bool is_parallel(const Vec3& a, const Vec3& b);
[[nodiscard]] bool is_perpendicular(const Vec3& a, const Vec3& b);

/**
 * @brief Computes mirror reflection of vector v off a surface with unit normal.
 * Formula: v - 2 * dot(v, normal) * normal
 * @pre normal must be a unit vector.
 */
[[nodiscard]] Vec3 reflect(const Vec3& v, const Vec3& normal);

/**
 * @brief Computes Snell's refraction of unit vector uv through a surface with unit normal n.
 * @pre uv and n must be unit vectors.
 */
[[nodiscard]] Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat);

/**
 * @brief Linear interpolation between two vectors.
 * Formula: (1 - t) * a + t * b
 */
[[nodiscard]] Vec3 lerp(const Vec3& a, const Vec3& b, double t);

// Spatial stochastic sampling
[[nodiscard]] Vec3 random_in_unit_sphere();
[[nodiscard]] Vec3 random_unit_vector();
[[nodiscard]] Vec3 random_in_unit_disk();

// Stream output
std::ostream& operator<<(std::ostream& os, const Vec3& v);

} // namespace lightrail
