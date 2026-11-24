/**
 * @file complex.hpp
 * @brief Complex number class @f$ z = r + i\cdot\text{im} \in \mathbb{C} @f$ satisfying Field and NormedAlgebra.
 * @see [Complex Number (Wikipedia)](https://en.wikipedia.org/wiki/Complex_number)
 */
#pragma once

#include <iosfwd>
#include "lightrail/math/algebra_structures.hpp"

namespace lightrail {

/**
 * @brief Complex number representation @f$ z = a + bi @f$ satisfying Field and NormedAlgebra.
 * @see [Complex Number (Wikipedia)](https://en.wikipedia.org/wiki/Complex_number)
 * @see [Euler's Formula (Wikipedia)](https://en.wikipedia.org/wiki/Euler%27s_formula)
 */
class Complex : public FieldInterface<Complex>, public VectorSpaceInterface<Complex, double> {
private:
    double r_{0.0};
    double i_{0.0};

public:
    constexpr Complex() noexcept : r_(0.0), i_(0.0) {}
    constexpr Complex(double r, double i) noexcept : r_(r), i_(i) {}
    constexpr Complex(double r) noexcept : r_(r), i_(0.0) {}

    [[nodiscard]] constexpr double real() const noexcept { return r_; }
    [[nodiscard]] constexpr double imag() const noexcept { return i_; }

    static constexpr Complex zero() noexcept { return Complex(0.0, 0.0); }
    static constexpr Complex one() noexcept { return Complex(1.0, 0.0); }

    Complex operator-() const;

    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    Complex operator/(const Complex& other) const;

    Complex operator*(double scalar) const;
    Complex operator/(double scalar) const;
    friend Complex operator*(double scalar, const Complex& c);

    bool operator==(const Complex& other) const;
    bool operator!=(const Complex& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

/**
 * @brief Computes the complex modulus @f$ |z| = \sqrt{\text{re}^2 + \text{im}^2} @f$.
 * @param c Complex number.
 * @return Euclidean modulus.
 */
double norm(const Complex& c);

/**
 * @brief Computes the complex exponential via Euler's formula: @f$ e^{a + bi} = e^a (\cos b + i\sin b) @f$.
 * @param c Complex exponent.
 * @return @f$ e^c @f$.
 * @see [Euler's Formula (Wikipedia)](https://en.wikipedia.org/wiki/Euler%27s_formula)
 */
Complex exp(const Complex& c);

/**
 * @brief Computes the principal complex natural logarithm: @f$ \ln(z) = \ln|z| + i\,\text{atan2}(\text{im}, \text{re}) @f$.
 * @param c Non-zero complex number.
 * @return Principal branch of @f$ \ln(c) @f$.
 * @see [Complex Logarithm (Wikipedia)](https://en.wikipedia.org/wiki/Complex_logarithm)
 */
Complex log(const Complex& c);

/**
 * @brief Computes the complex sine @f$ \sin(a + bi) = \sin a \cosh b + i \cos a \sinh b @f$.
 * @param c Complex angle.
 * @return @f$ \sin(c) @f$.
 */
Complex sin(const Complex& c);

/**
 * @brief Computes the complex cosine @f$ \cos(a + bi) = \cos a \cosh b - i \sin a \sinh b @f$.
 * @param c Complex angle.
 * @return @f$ \cos(c) @f$.
 */
Complex cos(const Complex& c);

} // namespace lightrail
