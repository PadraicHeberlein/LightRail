/**
 * @file algebra_concepts.hpp
 * @brief C++20 concepts encoding abstract algebraic structures (Group, Ring, Field, VectorSpace, Algebra, LieAlgebra).
 * @see [Constraints and Concepts in C++20 (cppreference)](https://en.cppreference.com/w/cpp/language/constraints)
 * @see [Abstract Algebra (Wikipedia)](https://en.wikipedia.org/wiki/Abstract_algebra)
 */
#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>
#include "lightrail/math/algebra_structures.hpp"

namespace lightrail {

/**
 * @brief Scalar concept: standard arithmetic built-in type (`int`, `float`, `double`, etc.).
 * @see [std::is_arithmetic (cppreference)](https://en.cppreference.com/w/cpp/types/is_arithmetic)
 */
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

/**
 * @brief Group concept under addition @f$ (G, +) @f$.
 *
 * Requires copyability, closure under addition and subtraction, additive identity `T(0)`,
 * additive inverse `-a`, and equality comparisons.
 *
 * @see [Group (Mathematics) (Wikipedia)](https://en.wikipedia.org/wiki/Group_(mathematics))
 */
template <typename T>
concept Group = std::copyable<T> && requires(const T a, const T b) {
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { T(0) } -> std::same_as<T>;
    { -a } -> std::same_as<T>;
    { a == b } -> std::same_as<bool>;
    { a != b } -> std::same_as<bool>;
};

/**
 * @brief Ring concept: an additive Group equipped with associative multiplication and multiplicative identity `T(1)`.
 * @see [Ring (Mathematics) (Wikipedia)](https://en.wikipedia.org/wiki/Ring_(mathematics))
 */
template <typename T>
concept Ring = Group<T> && requires(const T a, const T b) {
    { a * b } -> std::same_as<T>;
    { T(1) } -> std::same_as<T>;
};

/**
 * @brief DivisionRing (Skew Field) concept: a Ring where nonzero elements support division (e.g., Quaternions @f$ \mathbb{H} @f$).
 * @see [Division Ring (Wikipedia)](https://en.wikipedia.org/wiki/Division_ring)
 */
template <typename T>
concept DivisionRing = Ring<T> && requires(const T a, const T b) {
    { a / b } -> std::same_as<T>;
};

/**
 * @brief Field concept: a commutative Division Ring (e.g., @f$ \mathbb{R} @f$, @f$ \mathbb{C} @f$).
 *
 * Enforced via FieldInterface or built-in scalar types.
 *
 * @see [Field (Mathematics) (Wikipedia)](https://en.wikipedia.org/wiki/Field_(mathematics))
 */
template <typename T>
concept Field = DivisionRing<T> && (Scalar<T> || std::derived_from<T, FieldInterface<T>>);

/**
 * @brief VectorSpace concept over a scalar @p S (defaults to `double`).
 *
 * Requires vector addition and scalar multiplication/division.
 *
 * @see [Vector Space (Wikipedia)](https://en.wikipedia.org/wiki/Vector_space)
 */
template <typename V, typename S = double>
concept VectorSpace = Group<V> && Scalar<S> && requires(const V v, const S s) {
    { v * s } -> std::convertible_to<V>;
    { s * v } -> std::convertible_to<V>;
    { v / s } -> std::convertible_to<V>;
};

/**
 * @brief Algebra concept: a VectorSpace equipped with a bilinear Ring product.
 * @see [Algebra over a Field (Wikipedia)](https://en.wikipedia.org/wiki/Algebra_over_a_field)
 */
template <typename A, typename S = double>
concept Algebra = VectorSpace<A, S> && Ring<A>;

/**
 * @brief NormedAlgebra concept: an Algebra equipped with a submultiplicative norm function @f$ \|a\| @f$.
 * @see [Normed Algebra (Wikipedia)](https://en.wikipedia.org/wiki/Normed_algebra)
 */
template <typename T, typename S = double>
concept NormedAlgebra = Algebra<T, S> && requires(const T a) {
    { norm(a) } -> std::floating_point;
};

/**
 * @brief LieAlgebra concept: a VectorSpace equipped with an antisymmetric, bilinear commutator / Lie bracket @f$ [a, b] @f$.
 * @see [Lie Algebra (Wikipedia)](https://en.wikipedia.org/wiki/Lie_algebra)
 */
template <typename L, typename S = double>
concept LieAlgebra = VectorSpace<L, S> && requires(const L a, const L b) {
    { commutator(a, b) } -> std::same_as<L>;
};

/**
 * @brief Default absolute-value norm for built-in scalar arithmetic types.
 * @param x Scalar value.
 * @return @f$ |x| @f$ as a double.
 */
template <Scalar T>
inline double norm(T x) {
    return std::abs(static_cast<double>(x));
}

} // namespace lightrail
