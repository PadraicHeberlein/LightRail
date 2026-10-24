#include "lightrail/math/mat3.hpp"
#include "lightrail/math/quaternion.hpp"
#include <stdexcept>

namespace lightrail {

Mat3::Mat3() {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            m[r][c] = 0.0;
        }
    }
}

Mat3::Mat3(double diag) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            m[r][c] = (r == c) ? diag : 0.0;
        }
    }
}

Mat3::Mat3(double m00, double m01, double m02,
           double m10, double m11, double m12,
           double m20, double m21, double m22) {
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
}

Mat3 Mat3::identity() {
    // TODO: Implement 3x3 identity matrix (diagonal 1.0, off-diagonal 0.0)
    throw std::logic_error("Not implemented: Mat3::identity()");
}

Mat3 Mat3::zero() {
    return Mat3(0.0);
}

Mat3 Mat3::rotation_x(double radians) {
    // TODO: Implement rotation matrix around X-axis
    // [ 1       0            0     ]
    // [ 0   cos(theta)  -sin(theta)]
    // [ 0   sin(theta)   cos(theta)]
    throw std::logic_error("Not implemented: Mat3::rotation_x(radians)");
}

Mat3 Mat3::rotation_y(double radians) {
    // TODO: Implement rotation matrix around Y-axis
    // [ cos(theta)   0   sin(theta)]
    // [     0        1       0     ]
    // [-sin(theta)   0   cos(theta)]
    throw std::logic_error("Not implemented: Mat3::rotation_y(radians)");
}

Mat3 Mat3::rotation_z(double radians) {
    // TODO: Implement rotation matrix around Z-axis
    // [ cos(theta)  -sin(theta)  0 ]
    // [ sin(theta)   cos(theta)  0 ]
    // [     0            0       1 ]
    throw std::logic_error("Not implemented: Mat3::rotation_z(radians)");
}

Mat3 Mat3::from_quaternion(const Quaternion& q) {
    throw std::logic_error("Not implemented: Mat3::from_quaternion");
}

Vec3 Mat3::row(int r) const {
    // TODO: Return row r as a Vec3(m[r][0], m[r][1], m[r][2])
    throw std::logic_error("Not implemented: Mat3::row(r)");
}

Vec3 Mat3::col(int c) const {
    // TODO: Return column c as a Vec3(m[0][c], m[1][c], m[2][c])
    throw std::logic_error("Not implemented: Mat3::col(c)");
}

Mat3 Mat3::transpose() const {
    // TODO: Implement matrix transpose (swap rows and columns: res.m[i][j] = m[j][i])
    throw std::logic_error("Not implemented: Mat3::transpose()");
}

double Mat3::determinant() const {
    // TODO: Implement 3x3 matrix determinant expansion by minors:
    // m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])
    // - m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0])
    // + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0])
    throw std::logic_error("Not implemented: Mat3::determinant()");
}

std::optional<Mat3> Mat3::inverse() const {
    // TODO: Implement matrix inverse via adjugate matrix / determinant
    // Return std::nullopt if std::abs(det) < kEpsilon
    throw std::logic_error("Not implemented: Mat3::inverse()");
}

Quaternion Mat3::to_quaternion() const {
    throw std::logic_error("Not implemented: Mat3::to_quaternion");
}

Mat3 Mat3::operator-() const {
    throw std::logic_error("Not implemented: Mat3::operator-");
}

Mat3 Mat3::operator+(const Mat3& other) const {
    // TODO: Implement component-wise matrix addition
    throw std::logic_error("Not implemented: Mat3::operator+");
}

Mat3 Mat3::operator-(const Mat3& other) const {
    // TODO: Implement component-wise matrix subtraction
    throw std::logic_error("Not implemented: Mat3::operator-");
}

Mat3 Mat3::operator*(const Mat3& other) const {
    // TODO: Implement 3x3 matrix multiplication: res[i][j] = sum_k(m[i][k] * other.m[k][j])
    throw std::logic_error("Not implemented: Mat3::operator*(Mat3)");
}

Vec3 Mat3::operator*(const Vec3& v) const {
    // TODO: Implement matrix-vector multiplication: dot(row(i), v)
    throw std::logic_error("Not implemented: Mat3::operator*(Vec3)");
}

Mat3 Mat3::operator*(double s) const {
    // TODO: Implement matrix-scalar multiplication
    throw std::logic_error("Not implemented: Mat3::operator*(double)");
}

Mat3 Mat3::operator/(double s) const {
    throw std::logic_error("Not implemented: Mat3::operator/(double)");
}

bool Mat3::operator==(const Mat3& other) const {
    throw std::logic_error("Not implemented: Mat3::operator==");
}

bool Mat3::operator!=(const Mat3& other) const {
    return !(*this == other);
}

Mat3 operator*(double s, const Mat3& mat) {
    return mat * s;
}

double norm(const Mat3& mat) {
    throw std::logic_error("Not implemented: norm(Mat3)");
}

} // namespace lightrail
