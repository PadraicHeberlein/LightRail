#include "lightrail/math/quaternion.hpp"
#include "lightrail/math/mat3.hpp"
#include <iostream>
#include <stdexcept>

namespace lightrail {

Quaternion::Quaternion(double angle_radians, const Vec3& axis) {
    throw std::logic_error("Not implemented: Quaternion(angle, axis)");
}

Quaternion Quaternion::from_axis_angle(const Vec3& axis, double radians) {
    throw std::logic_error("Not implemented: Quaternion::from_axis_angle");
}

Quaternion Quaternion::from_mat3(const Mat3& m) {
    throw std::logic_error("Not implemented: Quaternion::from_mat3");
}

Quaternion Quaternion::operator-() const {
    throw std::logic_error("Not implemented: Quaternion::operator-");
}

Quaternion Quaternion::operator+(const Quaternion& other) const {
    throw std::logic_error("Not implemented: Quaternion::operator+");
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
    throw std::logic_error("Not implemented: Quaternion::operator-");
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    throw std::logic_error("Not implemented: Quaternion::operator*(Quaternion)");
}

Quaternion Quaternion::operator/(const Quaternion& other) const {
    throw std::logic_error("Not implemented: Quaternion::operator/(Quaternion)");
}

Quaternion Quaternion::operator*(double s) const {
    throw std::logic_error("Not implemented: Quaternion::operator*(double)");
}

Quaternion Quaternion::operator/(double s) const {
    throw std::logic_error("Not implemented: Quaternion::operator/(double)");
}

Quaternion operator*(double s, const Quaternion& q) {
    return q * s;
}

bool Quaternion::operator==(const Quaternion& other) const {
    throw std::logic_error("Not implemented: Quaternion::operator==");
}

bool Quaternion::operator!=(const Quaternion& other) const {
    return !(*this == other);
}

double Quaternion::norm() const {
    throw std::logic_error("Not implemented: Quaternion::norm");
}

double Quaternion::norm_squared() const {
    throw std::logic_error("Not implemented: Quaternion::norm_squared");
}

Quaternion Quaternion::normalized() const {
    throw std::logic_error("Not implemented: Quaternion::normalized");
}

Quaternion Quaternion::conjugate() const {
    throw std::logic_error("Not implemented: Quaternion::conjugate");
}

Quaternion Quaternion::inverse() const {
    throw std::logic_error("Not implemented: Quaternion::inverse");
}

Vec3 Quaternion::rotate(const Vec3& v) const {
    throw std::logic_error("Not implemented: Quaternion::rotate");
}

Mat3 Quaternion::to_mat3() const {
    throw std::logic_error("Not implemented: Quaternion::to_mat3");
}

std::pair<Vec3, double> Quaternion::to_axis_angle() const {
    throw std::logic_error("Not implemented: Quaternion::to_axis_angle");
}

std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
    os << "Quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
    return os;
}

double norm(const Quaternion& q) {
    return q.norm();
}

double dot(const Quaternion& a, const Quaternion& b) {
    throw std::logic_error("Not implemented: dot(Quaternion, Quaternion)");
}

Quaternion exp(const Quaternion& q) {
    throw std::logic_error("Not implemented: exp(Quaternion)");
}

Quaternion log(const Quaternion& q) {
    throw std::logic_error("Not implemented: log(Quaternion)");
}

Quaternion pow(const Quaternion& q, double t) {
    throw std::logic_error("Not implemented: pow(Quaternion, double)");
}

Quaternion sin(const Quaternion& q) {
    throw std::logic_error("Not implemented: sin(Quaternion)");
}

Quaternion cos(const Quaternion& q) {
    throw std::logic_error("Not implemented: cos(Quaternion)");
}

} // namespace lightrail
