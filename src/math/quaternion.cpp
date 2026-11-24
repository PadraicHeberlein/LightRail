#include <cmath>
#include <iostream>
#include <stdexcept>

#include "lightrail/math/constants.hpp"
#include "lightrail/math/mat3.hpp"
#include "lightrail/math/quaternion.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

Quaternion::Quaternion(double angle_radians, const Vec3& axis, double epsilon) noexcept {
    const double len_sq = axis.length_squared();

    if (len_sq <= epsilon * epsilon) {
        w = 1.0;
        x = 0.0;
        y = 0.0;
        z = 0.0;
        return;
    }

    const double half_angle = 0.5 * angle_radians;
    const double s = std::sin(half_angle) / std::sqrt(len_sq);

    w = std::cos(half_angle);
    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
}


Quaternion Quaternion::from_axis_angle(const Vec3& axis, double radians) {
    return Quaternion(radians, axis);
}

Quaternion Quaternion::from_mat3(const Mat3& mat) {
    const double trace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];

    if (trace > 0.0) {
        const double s = std::sqrt(trace + 1.0) * 2.0; // s = 4 * w
        return Quaternion(
            0.25 * s,
            (mat.m[2][1] - mat.m[1][2]) / s,
            (mat.m[0][2] - mat.m[2][0]) / s,
            (mat.m[1][0] - mat.m[0][1]) / s
        );
    } else if (mat.m[0][0] > mat.m[1][1] && mat.m[0][0] > mat.m[2][2]) {
        const double s = std::sqrt(1.0 + mat.m[0][0] - mat.m[1][1] - mat.m[2][2]) * 2.0; // s = 4 * x
        return Quaternion(
            (mat.m[2][1] - mat.m[1][2]) / s,
            0.25 * s,
            (mat.m[0][1] + mat.m[1][0]) / s,
            (mat.m[0][2] + mat.m[2][0]) / s
        );
    } else if (mat.m[1][1] > mat.m[2][2]) {
        const double s = std::sqrt(1.0 + mat.m[1][1] - mat.m[0][0] - mat.m[2][2]) * 2.0; // s = 4 * y
        return Quaternion(
            (mat.m[0][2] - mat.m[2][0]) / s,
            (mat.m[0][1] + mat.m[1][0]) / s,
            0.25 * s,
            (mat.m[1][2] + mat.m[2][1]) / s
        );
    } else {
        const double s = std::sqrt(1.0 + mat.m[2][2] - mat.m[0][0] - mat.m[1][1]) * 2.0; // s = 4 * z
        return Quaternion(
            (mat.m[1][0] - mat.m[0][1]) / s,
            (mat.m[0][2] + mat.m[2][0]) / s,
            (mat.m[1][2] + mat.m[2][1]) / s,
            0.25 * s
        );
    }
}

Quaternion Quaternion::operator-() const {
    return Quaternion(-w, -x, -y, -z);
}

Quaternion Quaternion::operator+(const Quaternion& other) const {
    return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
    return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z, 
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    );
}

Quaternion Quaternion::operator/(const Quaternion& other) const {
    return *this * other.inverse();
}

Quaternion Quaternion::operator*(double s) const {
    return Quaternion(w * s, x * s, y * s, z * s);
}

Quaternion Quaternion::operator/(double s) const {
    return Quaternion(w / s, x / s, y / s, z / s);
}

Quaternion operator*(double s, const Quaternion& q) {
    return q * s;
}

bool Quaternion::operator==(const Quaternion& other) const {
    return w == other.w && x == other.x && y == other.y && z == other.z;
}

bool Quaternion::operator!=(const Quaternion& other) const {
    return !(*this == other);
}

double Quaternion::norm() const {
    return std::sqrt(norm_squared());
}

double Quaternion::norm_squared() const {
    return w * w + x * x + y * y + z * z;
}

Quaternion Quaternion::normalized() const {
    const double n = norm();
    if (n == 0.0) {
        throw std::invalid_argument("Cannot normalize zero quaternion");
    }
    return *this / n;
}

Quaternion Quaternion::conjugate() const {
    return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::inverse() const {
    return conjugate() / norm_squared();
}

Vec3 Quaternion::rotate(const Vec3& v) const {
    const Quaternion q_v(0.0, v.x, v.y, v.z);
    const Quaternion q_conj = conjugate();
    const Quaternion result = *this * q_v * q_conj;
    return Vec3(result.x, result.y, result.z);
}

Mat3 Quaternion::to_mat3() const {
    return Mat3(
        1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y - z * w),     2.0 * (x * z + y * w),
        2.0 * (x * y + z * w),     1.0 - 2.0 * (x * x + z * z), 2.0 * (y * z - x * w),
        2.0 * (x * z - y * w),     2.0 * (y * z + x * w),     1.0 - 2.0 * (x * x + y * y)
    );
}

std::pair<Vec3, double> Quaternion::to_axis_angle() const {
    const double angle = 2.0 * std::acos(w);
    const double s = std::sqrt(1.0 - w * w);

    if (s < kEpsilon) {
        // If s is close to zero, the axis can be any normalized vector
        return {Vec3(1.0, 0.0, 0.0), angle};
    } else {
        return {Vec3(x / s, y / s, z / s), angle};
    }
}

std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
    os << "Quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
    return os;
}

double norm(const Quaternion& q) {
    return q.norm();
}

double dot(const Quaternion& a, const Quaternion& b) {
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

Quaternion exp(const Quaternion& q) {
    throw std::logic_error("Not implemented: exp(Quaternion)");
}

Quaternion log(const Quaternion& q) {
    throw std::logic_error("Not implemented: log(Quaternion)");
}

Quaternion pow(const Quaternion& q, double t) {
    throw std::logic_error("Not implemented: pow(Quaternion, double)");
}

Quaternion sin(const Quaternion& q) {
    throw std::logic_error("Not implemented: sin(Quaternion)");
}

Quaternion cos(const Quaternion& q) {
    throw std::logic_error("Not implemented: cos(Quaternion)");
}

} // namespace lightrail
