#pragma once

#include <iosfwd>
#include <utility>
#include "lightrail/math/algebra_structures.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

class Mat3;

/**
 * @brief Quaternion representation for 3D rotations and orientation algebra.
 * Models NormedAlgebra (and non-commutative Division Ring).
 */
class Quaternion : public NormedAlgebraInterface<Quaternion, double> {
public:
    double w{1.0};
    double x{0.0};
    double y{0.0};
    double z{0.0};

    // Constructors
    constexpr Quaternion() noexcept : w(1.0), x(0.0), y(0.0), z(0.0) {}
    constexpr Quaternion(double w, double x, double y, double z) noexcept
        : w(w), x(x), y(y), z(z) {}
    constexpr explicit Quaternion(double scalar) noexcept
        : w(scalar), x(0.0), y(0.0), z(0.0) {}
    Quaternion(double angle_radians, const Vec3& axis);

    // Static factories
    static constexpr Quaternion identity() noexcept { return Quaternion(1.0, 0.0, 0.0, 0.0); }
    static constexpr Quaternion zero() noexcept { return Quaternion(0.0, 0.0, 0.0, 0.0); }
    static Quaternion from_axis_angle(const Vec3& axis, double radians);
    static Quaternion from_mat3(const Mat3& m);

    // Algebraic operations
    Quaternion operator-() const;
    Quaternion operator+(const Quaternion& other) const;
    Quaternion operator-(const Quaternion& other) const;
    Quaternion operator*(const Quaternion& other) const;
    Quaternion operator/(const Quaternion& other) const;

    Quaternion operator*(double s) const;
    Quaternion operator/(double s) const;
    friend Quaternion operator*(double s, const Quaternion& q);

    bool operator==(const Quaternion& other) const;
    bool operator!=(const Quaternion& other) const;

    // Geometric & Norm operations
    double norm() const;
    double norm_squared() const;
    Quaternion normalized() const;
    Quaternion conjugate() const;
    Quaternion inverse() const;

    Vec3 rotate(const Vec3& v) const;
    Mat3 to_mat3() const;
    std::pair<Vec3, double> to_axis_angle() const;

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};

// Quaternion non-member functions & transcendentals
double norm(const Quaternion& q);
double dot(const Quaternion& a, const Quaternion& b);
Quaternion exp(const Quaternion& q);
Quaternion log(const Quaternion& q);
Quaternion pow(const Quaternion& q, double t);
Quaternion sin(const Quaternion& q);
Quaternion cos(const Quaternion& q);

} // namespace lightrail
