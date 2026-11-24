/**
 * @file algebra_structures.hpp
 * @brief Zero-overhead CRTP (Curiously Recurring Template Pattern) base tags modeling an explicit algebraic hierarchy.
 * @see [Curiously Recurring Template Pattern (Wikipedia)](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)
 * @see [Static Polymorphism / CRTP (cppreference)](https://en.cppreference.com/w/cpp/language/crtp)
 */
#pragma once

namespace lightrail {

/**
 * @brief CRTP base interface marking a type as an additive Group.
 * @tparam Derived Concrete algebraic type inheriting via CRTP.
 * @see [Group (Mathematics) (Wikipedia)](https://en.wikipedia.org/wiki/Group_(mathematics))
 */
template <typename Derived>
struct GroupInterface {
protected:
    GroupInterface() = default;
};

/**
 * @brief CRTP base interface marking a type as a Ring.
 * @tparam Derived Concrete algebraic type inheriting via CRTP.
 * @see [Ring (Mathematics) (Wikipedia)](https://en.wikipedia.org/wiki/Ring_(mathematics))
 */
template <typename Derived>
struct RingInterface : public GroupInterface<Derived> {
protected:
    RingInterface() = default;
};

/**
 * @brief CRTP base interface marking a type as a commutative Field (used by the Field concept).
 * @tparam Derived Concrete algebraic type inheriting via CRTP.
 * @see [Field (Mathematics) (Wikipedia)](https://en.wikipedia.org/wiki/Field_(mathematics))
 */
template <typename Derived>
struct FieldInterface : public RingInterface<Derived> {
protected:
    FieldInterface() = default;
};

/**
 * @brief CRTP base interface marking a type as a VectorSpace over @p Scalar.
 * @tparam Derived Concrete algebraic type inheriting via CRTP.
 * @tparam Scalar Underlying scalar field type (default `double`).
 * @see [Vector Space (Wikipedia)](https://en.wikipedia.org/wiki/Vector_space)
 */
template <typename Derived, typename Scalar = double>
struct VectorSpaceInterface : public GroupInterface<Derived> {
protected:
    VectorSpaceInterface() = default;
};

/**
 * @brief CRTP base interface marking a type as an Algebra (both Ring and VectorSpace).
 * @tparam Derived Concrete algebraic type inheriting via CRTP.
 * @tparam Scalar Underlying scalar field type (default `double`).
 * @see [Algebra over a Field (Wikipedia)](https://en.wikipedia.org/wiki/Algebra_over_a_field)
 */
template <typename Derived, typename Scalar = double>
struct AlgebraInterface : public RingInterface<Derived>, public VectorSpaceInterface<Derived, Scalar> {
protected:
    AlgebraInterface() = default;
};

/**
 * @brief CRTP base interface marking a type as a NormedAlgebra (e.g., Mat3, Quaternion).
 * @tparam Derived Concrete algebraic type inheriting via CRTP.
 * @tparam Scalar Underlying scalar field type (default `double`).
 * @see [Normed Algebra (Wikipedia)](https://en.wikipedia.org/wiki/Normed_algebra)
 */
template <typename Derived, typename Scalar = double>
struct NormedAlgebraInterface : public AlgebraInterface<Derived, Scalar> {
protected:
    NormedAlgebraInterface() = default;
};

} // namespace lightrail
