/**
 * @file quaternion.hpp
 * @brief Hamilton quaternion @f$ q = w + x\mathbf{i} + y\mathbf{j} + z\mathbf{k} \in \mathbb{H} @f$ for gimbal-lock-free 3D rotations.
 *
 * @image html lie_group_so3_map.svg "Unit quaternions as the double cover of SO(3)"
 *
 * @see [Quaternions and Spatial Rotation (Wikipedia)](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
 * @see [Quaternion (Wikipedia)](https://en.wikipedia.org/wiki/Quaternion)
 */
#pragma once

#include <iosfwd>
#include <utility>

#include "lightrail/math/algebra_structures.hpp"
#include "lightrail/math/constants.hpp"
#include "lightrail/math/mat3.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

class Mat3;

/**
 * @brief Quaternion representation @f$ q = w + x\mathbf{i} + y\mathbf{j} + z\mathbf{k} @f$ for 3D rotations and orientation algebra.
 *
 * Models NormedAlgebra and DivisionRing (non-commutative skew field @f$ \mathbb{H} @f$).
 * Unit quaternions (@f$ \|q\| = 1 @f$) form the 3-sphere @f$ S^3 @f$ and double-cover @f$ SO(3) @f$.
 *
 * @see [Quaternions and Spatial Rotation (Wikipedia)](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
 * @see [Visualizing Quaternions (3Blue1Brown / Ben Eater)](https://eater.net/quaternions)
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
    Quaternion(double angle_radians, const Vec3& axis, double epsilon = kEpsilon) noexcept;

    // Static factories
    static constexpr Quaternion identity() noexcept { return Quaternion(1.0, 0.0, 0.0, 0.0); }
    static constexpr Quaternion zero() noexcept { return Quaternion(0.0, 0.0, 0.0, 0.0); }

    /**
     * @brief Constructs a unit rotation quaternion from an @p axis and angle @f$ \theta @f$:
     * @f$ q = \cos(\theta/2) + \hat{\mathbf{u}}\sin(\theta/2) @f$.
     */
    static Quaternion from_axis_angle(const Vec3& axis, double radians);

    /**
     * @brief Converts a 3x3 @f$ SO(3) @f$ rotation matrix into a unit Quaternion.
     */
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
    [[nodiscard]] double norm() const;
    [[nodiscard]] double norm_squared() const;
    [[nodiscard]] Quaternion normalized() const;

    /**
     * @brief Returns the quaternion conjugate @f$ q^* = w - x\mathbf{i} - y\mathbf{j} - z\mathbf{k} @f$.
     */
    [[nodiscard]] Quaternion conjugate() const;

    /**
     * @brief Returns the multiplicative inverse @f$ q^{-1} = q^* / \|q\|^2 @f$.
     */
    [[nodiscard]] Quaternion inverse() const;

    /**
     * @brief Rotates a 3D vector @p v via the unit-quaternion sandwich product @f$ \mathbf{v}' = q (0, \mathbf{v}) q^* @f$.
     * @param v 3D vector to rotate.
     * @return Rotated 3D vector.
     * @pre This quaternion must be unit-length (@f$ \|q\| = 1 @f$).
     */
    [[nodiscard]] Vec3 rotate(const Vec3& v) const;

    [[nodiscard]] Mat3 to_mat3() const;
    [[nodiscard]] std::pair<Vec3, double> to_axis_angle() const;

    friend std::ostream& operator<<(std::ostream& os, const Quaternion& q);
};

// Quaternion non-member functions & transcendentals
double norm(const Quaternion& q);
double dot(const Quaternion& a, const Quaternion& b);

/**
 * @brief Closed-form quaternion exponential: @f$ \exp(w + \mathbf{v}) = e^w (\cos\|\mathbf{v}\| + \hat{\mathbf{v}}\sin\|\mathbf{v}\|) @f$.
 * @see [Quaternion Exponential, Logarithm, and Power (Wikipedia)](https://en.wikipedia.org/wiki/Quaternion#Exponential,_logarithm,_and_power_functions)
 */
Quaternion exp(const Quaternion& q);

/**
 * @brief Closed-form quaternion natural logarithm: @f$ \log(q) = \ln\|q\| + \hat{\mathbf{v}}\arccos(w / \|q\|) @f$.
 */
Quaternion log(const Quaternion& q);

/**
 * @brief Raises a quaternion to a real power @p t: @f$ q^t = \exp(t \log(q)) @f$.
 */
Quaternion pow(const Quaternion& q, double t);
Quaternion sin(const Quaternion& q);
Quaternion cos(const Quaternion& q);

} // namespace lightrail
