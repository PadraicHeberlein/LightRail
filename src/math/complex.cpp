#include "lightrail/math/complex.hpp"
#include <iostream>
#include <stdexcept>

namespace lightrail {

Complex Complex::operator-() const {
    throw std::logic_error("Not implemented: Complex::operator-");
}

Complex Complex::operator+(const Complex& other) const {
    throw std::logic_error("Not implemented: Complex::operator+");
}

Complex Complex::operator-(const Complex& other) const {
    throw std::logic_error("Not implemented: Complex::operator-");
}

Complex Complex::operator*(const Complex& other) const {
    throw std::logic_error("Not implemented: Complex::operator*(Complex)");
}

Complex Complex::operator/(const Complex& other) const {
    throw std::logic_error("Not implemented: Complex::operator/(Complex)");
}

Complex Complex::operator*(double scalar) const {
    throw std::logic_error("Not implemented: Complex::operator*(double)");
}

Complex Complex::operator/(double scalar) const {
    throw std::logic_error("Not implemented: Complex::operator/(double)");
}

Complex operator*(double scalar, const Complex& c) {
    return c * scalar;
}

bool Complex::operator==(const Complex& other) const {
    throw std::logic_error("Not implemented: Complex::operator==");
}

bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real() << " + " << c.imag() << "i)";
    return os;
}

double norm(const Complex& c) {
    throw std::logic_error("Not implemented: norm(Complex)");
}

Complex exp(const Complex& c) {
    throw std::logic_error("Not implemented: exp(Complex)");
}

Complex log(const Complex& c) {
    throw std::logic_error("Not implemented: log(Complex)");
}

Complex sin(const Complex& c) {
    throw std::logic_error("Not implemented: sin(Complex)");
}

Complex cos(const Complex& c) {
    throw std::logic_error("Not implemented: cos(Complex)");
}

} // namespace lightrail
