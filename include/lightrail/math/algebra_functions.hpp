#pragma once

#include <type_traits>
#include <stdexcept>
#include "lightrail/math/algebra_concepts.hpp"
#include "lightrail/math/complex.hpp"
#include "lightrail/math/quaternion.hpp"
#include "lightrail/math/mat3.hpp"

namespace lightrail {

/**
 * @brief Helper to retrieve the identity element of an Algebra or Ring.
 */
template <typename T>
constexpr T identity_element() {
    if constexpr (requires { T::identity(); }) {
        return T::identity();
    } else {
        return T(1);
    }
}

/**
 * @brief Helper to retrieve the zero element of an additive Group.
 */
template <typename T>
constexpr T zero_element() {
    if constexpr (requires { T::zero(); }) {
        return T::zero();
    } else {
        return T(0);
    }
}

/**
 * @brief Generic Exponential function using Taylor Series expansion.
 * Valid for any type satisfying the Algebra concept.
 */
template <Algebra T>
T exp_taylor(const T& x, int terms = 50);

/**
 * @brief Generic Sine function using Taylor Series expansion.
 */
template <Algebra T>
T sin_taylor(const T& x, int terms = 50);

/**
 * @brief Generic Cosine function using Taylor Series expansion.
 */
template <Algebra T>
T cos_taylor(const T& x, int terms = 50);

/**
 * @brief Generic Natural Logarithm via Taylor series expansion: ln(I + (x - I)).
 */
template <Algebra T>
T log_taylor(const T& x, int terms = 50);

/**
 * @brief Generic power via repeated squaring for any Ring.
 */
template <Ring T>
T pow_algebra(const T& x, int exponent);

/**
 * @brief Factorial operator on an Algebra.
 */
template <Algebra T>
T factorial(int n);

/**
 * @brief Lie bracket / commutator: [a, b] = a * b - b * a.
 */
template <Ring T>
T commutator(const T& a, const T& b);

/**
 * @brief Geodesic / SLERP interpolation on Lie groups: a * exp(t * log(a^-1 * b)).
 * Shared operational implementation for both Quaternions and Rotation Matrices!
 */
template <typename T>
T slerp_algebraic(const T& a, const T& b, double t);

// =========================================================================
// Matrix-Quaternion Optimization Bridges
// =========================================================================

/**
 * @brief Optimizes rotation matrix multiplication by composing rotations in the quaternion domain.
 * Avoids 27 multiplications of 3x3 matrices in favor of 16 quaternion multiplications.
 */
Mat3 optimize_rotation_multiply(const Mat3& a, const Mat3& b);

/**
 * @brief Computes matrix exponential for skew-symmetric so(3) generators using closed-form quaternion exp.
 * Evaluates in O(1) without requiring numerical Taylor series approximations.
 */
Mat3 exp_skew_symmetric(const Mat3& omega);

/**
 * @brief Computes matrix logarithm for SO(3) rotation matrices via quaternion logarithmic mapping.
 */
Mat3 log_rotation_matrix(const Mat3& r);

} // namespace lightrail
