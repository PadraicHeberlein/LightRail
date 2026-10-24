#pragma once

namespace lightrail {

/**
 * @brief Base interfaces for algebraic structures using CRTP (Curiously Recurring Template Pattern).
 * Maintains compile-time zero runtime overhead while enforcing an explicit algebraic hierarchy.
 */

template <typename Derived>
struct GroupInterface {
protected:
    GroupInterface() = default;
};

template <typename Derived>
struct RingInterface : public GroupInterface<Derived> {
protected:
    RingInterface() = default;
};

template <typename Derived>
struct FieldInterface : public RingInterface<Derived> {
protected:
    FieldInterface() = default;
};

template <typename Derived, typename Scalar = double>
struct VectorSpaceInterface : public GroupInterface<Derived> {
protected:
    VectorSpaceInterface() = default;
};

template <typename Derived, typename Scalar = double>
struct AlgebraInterface : public RingInterface<Derived>, public VectorSpaceInterface<Derived, Scalar> {
protected:
    AlgebraInterface() = default;
};

template <typename Derived, typename Scalar = double>
struct NormedAlgebraInterface : public AlgebraInterface<Derived, Scalar> {
protected:
    NormedAlgebraInterface() = default;
};

} // namespace lightrail
