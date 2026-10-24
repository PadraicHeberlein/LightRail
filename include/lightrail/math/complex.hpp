#pragma once

#include <iosfwd>
#include "lightrail/math/algebra_structures.hpp"

namespace lightrail {

/**
 * @brief Complex number representation satisfying Field and NormedAlgebra.
 */
class Complex : public FieldInterface<Complex>, public VectorSpaceInterface<Complex, double> {
private:
    double r_{0.0};
    double i_{0.0};

public:
    constexpr Complex() noexcept : r_(0.0), i_(0.0) {}
    constexpr Complex(double r, double i) noexcept : r_(r), i_(i) {}
    constexpr Complex(double r) noexcept : r_(r), i_(0.0) {}

    Complex(const Complex&) = default;
    Complex(Complex&&) noexcept = default;
    Complex& operator=(const Complex&) = default;
    Complex& operator=(Complex&&) noexcept = default;
    ~Complex() = default;

    constexpr double real() const noexcept { return r_; }
    constexpr double imag() const noexcept { return i_; }

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

double norm(const Complex& c);
Complex exp(const Complex& c);
Complex log(const Complex& c);
Complex sin(const Complex& c);
Complex cos(const Complex& c);

} // namespace lightrail
