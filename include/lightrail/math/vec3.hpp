#pragma once

#include <cmath>
#include <iostream>
#include "lightrail/math/constants.hpp"

namespace lightrail {

struct Vec3 {
    double x{0.0};
    double y{0.0};
    double z{0.0};

    constexpr Vec3() noexcept = default;
    constexpr Vec3(double x, double y, double z) noexcept : x(x), y(y), z(z) {}

    // Coordinate access via index
    constexpr double operator[](std::size_t i) const noexcept {
        return (i == 0) ? x : (i == 1) ? y : z;
    }

    constexpr double& operator[](std::size_t i) noexcept {
        return (i == 0) ? x : (i == 1) ? y : z;
    }

    // Unary negation
    constexpr Vec3 operator-() const noexcept {
        return Vec3(-x, -y, -z);
    }

    // Compound assignment operators
    constexpr Vec3& operator+=(const Vec3& v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    constexpr Vec3& operator-=(const Vec3& v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    constexpr Vec3& operator*=(double s) noexcept {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    constexpr Vec3& operator*=(const Vec3& v) noexcept {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }

    constexpr Vec3& operator/=(double s) noexcept {
        return *this *= (1.0 / s);
    }

    // Length and magnitude operations
    constexpr double length_squared() const noexcept {
        return x * x + y * y + z * z;
    }

    double length() const noexcept {
        return std::sqrt(length_squared());
    }

    // Equality comparison with tolerance
    constexpr bool approx_equal(const Vec3& other, double eps = kEpsilon) const noexcept {
        return std::abs(x - other.x) < eps &&
               std::abs(y - other.y) < eps &&
               std::abs(z - other.z) < eps;
    }

    // Common basis vectors
    static constexpr Vec3 zero() noexcept { return Vec3(0.0, 0.0, 0.0); }
    static constexpr Vec3 unit_x() noexcept { return Vec3(1.0, 0.0, 0.0); }
    static constexpr Vec3 unit_y() noexcept { return Vec3(0.0, 1.0, 0.0); }
    static constexpr Vec3 unit_z() noexcept { return Vec3(0.0, 0.0, 1.0); }
};

// Aliasing Point3 to Vec3 for spatial points in 3D
using Point3 = Vec3;

// Binary arithmetic operators
constexpr Vec3 operator+(const Vec3& u, const Vec3& v) noexcept {
    return Vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

constexpr Vec3 operator-(const Vec3& u, const Vec3& v) noexcept {
    return Vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

// Component-wise multiplication (Hadamard product - great for color filtering)
constexpr Vec3 operator*(const Vec3& u, const Vec3& v) noexcept {
    return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

constexpr Vec3 operator*(double s, const Vec3& v) noexcept {
    return Vec3(s * v.x, s * v.y, s * v.z);
}

constexpr Vec3 operator*(const Vec3& v, double s) noexcept {
    return s * v;
}

constexpr Vec3 operator/(const Vec3& v, double s) noexcept {
    return (1.0 / s) * v;
}

// Vector operations
constexpr double dot(const Vec3& u, const Vec3& v) noexcept {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

constexpr Vec3 cross(const Vec3& u, const Vec3& v) noexcept {
    return Vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

inline Vec3 unit_vector(const Vec3& v) noexcept {
    double len = v.length();
    return (len > 0.0) ? (v / len) : Vec3::zero();
}

// Ray reflection: reflects ray v against surface normal n
// Note: Assumes n is a unit vector
constexpr Vec3 reflect(const Vec3& v, const Vec3& n) noexcept {
    return v - 2.0 * dot(v, n) * n;
}

// Refraction following Snell's Law
inline Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) noexcept {
    double cos_theta = std::fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -std::sqrt(std::abs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

// Semantic checks from original C# codebase
constexpr bool is_zero(const Vec3& v, double eps = kEpsilon) noexcept {
    return std::abs(v.x) < eps && std::abs(v.y) < eps && std::abs(v.z) < eps;
}

constexpr bool is_parallel(const Vec3& u, const Vec3& v, double eps = kEpsilon) noexcept {
    return is_zero(cross(u, v), eps);
}

constexpr bool is_perpendicular(const Vec3& u, const Vec3& v, double eps = kEpsilon) noexcept {
    return std::abs(dot(u, v)) < eps;
}

// Linear interpolation
constexpr Vec3 lerp(const Vec3& a, const Vec3& b, double t) noexcept {
    return (1.0 - t) * a + t * b;
}

// Stream insertion
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

} // namespace lightrail
