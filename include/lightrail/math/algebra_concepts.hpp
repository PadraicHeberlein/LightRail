#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>
#include "lightrail/math/algebra_structures.hpp"

namespace lightrail {

/**
 * @brief Scalar concept: standard arithmetic built-in type.
 */
template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

/**
 * @brief Group concept under addition.
 * Requires copyability, closure under addition & subtraction,
 * zero identity, additive inverse, and equality comparisons.
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
 * @brief Ring concept: an additive Group equipped with associative multiplication and identity.
 */
template <typename T>
concept Ring = Group<T> && requires(const T a, const T b) {
    { a * b } -> std::same_as<T>;
    { T(1) } -> std::same_as<T>;
};

/**
 * @brief DivisionRing (Skew Field) concept: a Ring where elements have division.
 */
template <typename T>
concept DivisionRing = Ring<T> && requires(const T a, const T b) {
    { a / b } -> std::same_as<T>;
};

/**
 * @brief Field concept: a commutative Division Ring.
 * Enforced via FieldInterface or built-in scalar types.
 */
template <typename T>
concept Field = DivisionRing<T> && (Scalar<T> || std::derived_from<T, FieldInterface<T>>);

/**
 * @brief VectorSpace concept over a scalar S (defaults to double).
 * Requires vector addition and scalar multiplication/division.
 */
template <typename V, typename S = double>
concept VectorSpace = Group<V> && Scalar<S> && requires(const V v, const S s) {
    { v * s } -> std::convertible_to<V>;
    { s * v } -> std::convertible_to<V>;
    { v / s } -> std::convertible_to<V>;
};

/**
 * @brief Algebra concept: a VectorSpace that is also a Ring.
 */
template <typename A, typename S = double>
concept Algebra = VectorSpace<A, S> && Ring<A>;

/**
 * @brief NormedAlgebra concept: an Algebra equipped with a norm function.
 */
template <typename T, typename S = double>
concept NormedAlgebra = Algebra<T, S> && requires(const T a) {
    { norm(a) } -> std::floating_point;
};

/**
 * @brief LieAlgebra concept: VectorSpace equipped with a commutator / Lie bracket.
 */
template <typename L, typename S = double>
concept LieAlgebra = VectorSpace<L, S> && requires(const L a, const L b) {
    { commutator(a, b) } -> std::same_as<L>;
};

// Default norm for scalar arithmetic types
template <Scalar T>
inline double norm(T x) {
    return std::abs(static_cast<double>(x));
}

} // namespace lightrail
