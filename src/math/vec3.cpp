#include <cassert>
#include <cmath>
#include <iostream>

#include "lightrail/math/vec3.hpp"

namespace lightrail {

double Vec3::length() const {
    return std::sqrt(length_squared());
}

double Vec3::length_squared() const {
    return x * x + y * y + z * z;
}

bool Vec3::approx_equal(const Vec3& other, double epsilon) const {
    return std::abs(x - other.x) < epsilon &&
           std::abs(y - other.y) < epsilon &&
           std::abs(z - other.z) < epsilon;
}

Vec3& Vec3::operator+=(const Vec3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3& Vec3::operator-=(const Vec3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3& Vec3::operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vec3& Vec3::operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

Vec3 Vec3::operator-() const {
    return Vec3(-x, -y, -z);
}

Vec3 operator+(const Vec3& a, const Vec3& b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator*(const Vec3& a, const Vec3& b) {
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3 operator*(double s, const Vec3& v) {
    return Vec3(s * v.x, s * v.y, s * v.z);
}

Vec3 operator*(const Vec3& v, double s) {
    return Vec3(s * v.x, s * v.y, s * v.z);
}

Vec3 operator/(const Vec3& v, double s) {
    return Vec3(v.x / s, v.y / s, v.z / s);
}

double dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

Vec3 unit_vector(const Vec3& v) {
    const double len = v.length();
    assert(len > 0.0 && "Cannot normalize a zero-length Vec3");
    return v / len;
}

bool is_parallel(const Vec3& a, const Vec3& b) {
    return cross(a, b).length_squared() <= kEpsilon * kEpsilon * a.length_squared() * b.length_squared();
}

bool is_perpendicular(const Vec3& a, const Vec3& b) {
    const double d = dot(a, b);
    return d * d <= kEpsilon * kEpsilon * a.length_squared() * b.length_squared();
}

Vec3 reflect(const Vec3& v, const Vec3& normal) {
    return v - 2.0 * dot(v, normal) * normal;
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    double cos_theta = std::fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

Vec3 lerp(const Vec3& a, const Vec3& b, double t) {
    return (1.0 - t) * a + t * b;
}

Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 p(random_double(-1.0, 1.0), random_double(-1.0, 1.0), random_double(-1.0, 1.0));
        if (p.length_squared() < 1.0) {
            return p;
        }
    }
}

Vec3 random_unit_vector() {
    while (true) {
        Vec3 p = random_in_unit_sphere();
        double len_sq = p.length_squared();
        if (len_sq > 1e-160) {
            return p / std::sqrt(len_sq);
        }
    }
}

Vec3 random_in_unit_disk() {
    while (true) {
        Vec3 p = Vec3(random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0.0);
        if (p.length_squared() < 1.0) {
            return p;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
}

} // namespace lightrail
