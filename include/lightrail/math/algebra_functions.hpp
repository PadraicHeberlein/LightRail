/**
 * @file algebra_functions.hpp
 * @brief Generic algebraic transcendentals (Taylor series), Lie brackets, geodesic SLERP, and SO(3)/Quaternion bridges.
 *
 * @image html lie_group_so3_map.svg "Mapping between Lie algebra so(3), rotation group SO(3), and unit quaternions"
 *
 * @see [Lie Group (Wikipedia)](https://en.wikipedia.org/wiki/Lie_group)
 * @see [3D Rotation Group SO(3) (Wikipedia)](https://en.wikipedia.org/wiki/3D_rotation_group)
 */
#pragma once

#include <type_traits>
#include "lightrail/math/algebra_concepts.hpp"
#include "lightrail/math/complex.hpp"
#include "lightrail/math/mat3.hpp"
#include "lightrail/math/quaternion.hpp"

namespace lightrail {

/**
 * @brief Retrieves the multiplicative identity element @f$ 1 @f$ or @f$ I @f$ of an Algebra or Ring.
 * @tparam T Ring or Algebra type.
 * @return Multiplicative identity of @p T.
 * @see [Identity Element (Wikipedia)](https://en.wikipedia.org/wiki/Identity_element)
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
 * @brief Retrieves the additive zero element @f$ 0 @f$ of an additive Group.
 * @tparam T Group type.
 * @return Additive identity of @p T.
 * @see [Additive Identity (Wikipedia)](https://en.wikipedia.org/wiki/Additive_identity)
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
 * @brief Generic exponential function via Taylor series expansion:
 * @f$ \exp(x) = \sum_{k=0}^{N-1} \frac{x^k}{k!} @f$.
 *
 * Valid for any type satisfying the Algebra concept (scalars, complex numbers, matrices, quaternions).
 *
 * @tparam T Algebra type.
 * @param x Input element.
 * @param terms Number of series terms to sum.
 * @return Approximation of @f$ \exp(x) @f$.
 * @see [Matrix Exponential (Wikipedia)](https://en.wikipedia.org/wiki/Matrix_exponential)
 * @see [Taylor Series (Wikipedia)](https://en.wikipedia.org/wiki/Taylor_series)
 */
template <Algebra T>
T exp_taylor(const T& x, int terms = 50);

/**
 * @brief Generic sine function via Taylor series expansion:
 * @f$ \sin(x) = \sum_{k=0}^{N-1} (-1)^k \frac{x^{2k+1}}{(2k+1)!} @f$.
 * @tparam T Algebra type.
 * @param x Input element.
 * @param terms Number of series terms to sum.
 * @return Approximation of @f$ \sin(x) @f$.
 * @see [Taylor Series (Wikipedia)](https://en.wikipedia.org/wiki/Taylor_series)
 */
template <Algebra T>
T sin_taylor(const T& x, int terms = 50);

/**
 * @brief Generic cosine function via Taylor series expansion:
 * @f$ \cos(x) = \sum_{k=0}^{N-1} (-1)^k \frac{x^{2k}}{(2k)!} @f$.
 * @tparam T Algebra type.
 * @param x Input element.
 * @param terms Number of series terms to sum.
 * @return Approximation of @f$ \cos(x) @f$.
 * @see [Taylor Series (Wikipedia)](https://en.wikipedia.org/wiki/Taylor_series)
 */
template <Algebra T>
T cos_taylor(const T& x, int terms = 50);

/**
 * @brief Generic natural logarithm via Mercator / Taylor series expansion:
 * @f$ \ln(I + (x - I)) = \sum_{k=1}^{N} (-1)^{k-1} \frac{(x - I)^k}{k} @f$.
 * @tparam T Algebra type.
 * @param x Input element near the identity (@f$ \|x - I\| < 1 @f$ for convergence).
 * @param terms Number of series terms to sum.
 * @return Approximation of @f$ \ln(x) @f$.
 * @see [Logarithm of a Matrix (Wikipedia)](https://en.wikipedia.org/wiki/Logarithm_of_a_matrix)
 */
template <Algebra T>
T log_taylor(const T& x, int terms = 50);

/**
 * @brief Generic integer power @f$ x^n @f$ via binary exponentiation (repeated squaring) in @f$ O(\log n) @f$ multiplications.
 * @tparam T Ring type.
 * @param x Base element.
 * @param exponent Non-negative integer exponent.
 * @return @f$ x^{\text{exponent}} @f$.
 * @see [Exponentiation by Squaring (Wikipedia)](https://en.wikipedia.org/wiki/Exponentiation_by_squaring)
 */
template <Ring T>
T pow_algebra(const T& x, int exponent);

/**
 * @brief Computes @f$ n! \cdot I @f$ in an Algebra.
 * @tparam T Algebra type.
 * @param n Non-negative integer.
 * @return @f$ n! @f$ scaled by the algebra's identity element.
 */
template <Algebra T>
T factorial(int n);

/**
 * @brief Lie bracket / ring commutator: @f$ [a, b] = a \cdot b - b \cdot a @f$.
 * @tparam T Ring type.
 * @param a First element.
 * @param b Second element.
 * @return Commutator @f$ [a, b] @f$ (zero if @p a and @p b commute).
 * @see [Commutator (Wikipedia)](https://en.wikipedia.org/wiki/Commutator)
 * @see [Lie Algebra (Wikipedia)](https://en.wikipedia.org/wiki/Lie_algebra)
 */
template <Ring T>
T commutator(const T& a, const T& b);

/**
 * @brief Geodesic / SLERP interpolation on Lie groups: @f$ a \cdot \exp\!\left(t \cdot \log(a^{-1} b)\right) @f$.
 *
 * Provides a unified operational implementation for both unit Quaternions and @f$ SO(3) @f$ rotation matrices.
 *
 * @tparam T Lie group element type (e.g., Quaternion or Mat3).
 * @param a Starting orientation (@f$ t = 0 @f$).
 * @param b Ending orientation (@f$ t = 1 @f$).
 * @param t Interpolation parameter in @f$ [0, 1] @f$.
 * @return Interpolated orientation along the shortest geodesic arc.
 * @see [Slerp (Wikipedia)](https://en.wikipedia.org/wiki/Slerp)
 * @see [Exponential Map (Lie Theory) (Wikipedia)](https://en.wikipedia.org/wiki/Exponential_map_(Lie_theory))
 */
template <typename T>
T slerp_algebraic(const T& a, const T& b, double t);

// =========================================================================
// Matrix-Quaternion Optimization Bridges
// =========================================================================

/**
 * @brief Optimizes rotation matrix multiplication by composing rotations in the quaternion domain.
 *
 * Avoids 27 multiplications of 3x3 matrices in favor of 16 quaternion multiplications.
 *
 * @param a First @f$ SO(3) @f$ rotation matrix.
 * @param b Second @f$ SO(3) @f$ rotation matrix.
 * @return Composed rotation matrix @f$ a \cdot b @f$.
 * @see [Conversion Between Quaternions and Euler Angles / Rotation Matrices (Wikipedia)](https://en.wikipedia.org/wiki/Rotation_matrix#Quaternion)
 */
Mat3 optimize_rotation_multiply(const Mat3& a, const Mat3& b);

/**
 * @brief Computes the matrix exponential @f$ \exp(\omega) \in SO(3) @f$ for a skew-symmetric @f$ \mathfrak{so}(3) @f$ generator using closed-form quaternion `exp`.
 *
 * Evaluates in @f$ O(1) @f$ without requiring numerical Taylor series approximations (equivalent to Rodrigues' rotation formula).
 *
 * @param omega Skew-symmetric 3x3 matrix (@f$ \omega^T = -\omega @f$).
 * @return Corresponding 3x3 rotation matrix in @f$ SO(3) @f$.
 * @see [Rodrigues' Rotation Formula (Wikipedia)](https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula)
 * @see [Axis-Angle Representation & Exponential Map (Wikipedia)](https://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation#Exponential_map_from_so(3)_to_SO(3))
 */
Mat3 exp_skew_symmetric(const Mat3& omega);

/**
 * @brief Computes the matrix logarithm @f$ \log(R) \in \mathfrak{so}(3) @f$ for an @f$ SO(3) @f$ rotation matrix via quaternion logarithmic mapping.
 * @param r Orthogonal 3x3 rotation matrix (@f$ R^T R = I, \det(R) = +1 @f$).
 * @return Skew-symmetric generator matrix in @f$ \mathfrak{so}(3) @f$.
 * @see [Axis-Angle Representation & Log Map (Wikipedia)](https://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation#Log_map_from_SO(3)_to_so(3))
 */
Mat3 log_rotation_matrix(const Mat3& r);

} // namespace lightrail
