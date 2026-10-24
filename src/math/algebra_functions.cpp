#include "lightrail/math/algebra_functions.hpp"
#include <stdexcept>

namespace lightrail {

template <Algebra T>
T exp_taylor(const T& x, int terms) {
    throw std::logic_error("Not implemented: exp_taylor");
}

template <Algebra T>
T sin_taylor(const T& x, int terms) {
    throw std::logic_error("Not implemented: sin_taylor");
}

template <Algebra T>
T cos_taylor(const T& x, int terms) {
    throw std::logic_error("Not implemented: cos_taylor");
}

template <Algebra T>
T log_taylor(const T& x, int terms) {
    throw std::logic_error("Not implemented: log_taylor");
}

template <Ring T>
T pow_algebra(const T& x, int exponent) {
    throw std::logic_error("Not implemented: pow_algebra");
}

template <Algebra T>
T factorial(int n) {
    throw std::logic_error("Not implemented: factorial");
}

template <Ring T>
T commutator(const T& a, const T& b) {
    throw std::logic_error("Not implemented: commutator");
}

template <typename T>
T slerp_algebraic(const T& a, const T& b, double t) {
    throw std::logic_error("Not implemented: slerp_algebraic");
}

Mat3 optimize_rotation_multiply(const Mat3& a, const Mat3& b) {
    throw std::logic_error("Not implemented: optimize_rotation_multiply");
}

Mat3 exp_skew_symmetric(const Mat3& omega) {
    throw std::logic_error("Not implemented: exp_skew_symmetric");
}

Mat3 log_rotation_matrix(const Mat3& r) {
    throw std::logic_error("Not implemented: log_rotation_matrix");
}

// Explicit template instantiations for core types
template double exp_taylor<double>(const double&, int);
template Complex exp_taylor<Complex>(const Complex&, int);
template Quaternion exp_taylor<Quaternion>(const Quaternion&, int);
template Mat3 exp_taylor<Mat3>(const Mat3&, int);

template double sin_taylor<double>(const double&, int);
template Complex sin_taylor<Complex>(const Complex&, int);
template Quaternion sin_taylor<Quaternion>(const Quaternion&, int);
template Mat3 sin_taylor<Mat3>(const Mat3&, int);

template double cos_taylor<double>(const double&, int);
template Complex cos_taylor<Complex>(const Complex&, int);
template Quaternion cos_taylor<Quaternion>(const Quaternion&, int);
template Mat3 cos_taylor<Mat3>(const Mat3&, int);

template double log_taylor<double>(const double&, int);
template Complex log_taylor<Complex>(const Complex&, int);
template Quaternion log_taylor<Quaternion>(const Quaternion&, int);
template Mat3 log_taylor<Mat3>(const Mat3&, int);

template double pow_algebra<double>(const double&, int);
template Complex pow_algebra<Complex>(const Complex&, int);
template Quaternion pow_algebra<Quaternion>(const Quaternion&, int);
template Mat3 pow_algebra<Mat3>(const Mat3&, int);

template double factorial<double>(int);
template Complex factorial<Complex>(int);
template Quaternion factorial<Quaternion>(int);
template Mat3 factorial<Mat3>(int);

template double commutator<double>(const double&, const double&);
template Complex commutator<Complex>(const Complex&, const Complex&);
template Quaternion commutator<Quaternion>(const Quaternion&, const Quaternion&);
template Mat3 commutator<Mat3>(const Mat3&, const Mat3&);

template Quaternion slerp_algebraic<Quaternion>(const Quaternion&, const Quaternion&, double);
template Mat3 slerp_algebraic<Mat3>(const Mat3&, const Mat3&, double);

} // namespace lightrail
