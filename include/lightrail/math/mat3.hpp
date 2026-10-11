#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <optional>
#include "lightrail/math/constants.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

class Mat3 {
public:
    // Row-major storage: e[row][col]
    std::array<std::array<double, 3>, 3> e{};

    constexpr Mat3() noexcept = default;

    constexpr Mat3(double m00, double m01, double m02,
                   double m10, double m11, double m12,
                   double m20, double m21, double m22) noexcept
        : e{{{m00, m01, m02}, {m10, m11, m12}, {m20, m21, m22}}} {}

    // Construct from 3 row vectors or 3 column vectors
    static constexpr Mat3 from_rows(const Vec3& r0, const Vec3& r1, const Vec3& r2) noexcept {
        return Mat3(
            r0.x, r0.y, r0.z,
            r1.x, r1.y, r1.z,
            r2.x, r2.y, r2.z
        );
    }

    static constexpr Mat3 from_cols(const Vec3& c0, const Vec3& c1, const Vec3& c2) noexcept {
        return Mat3(
            c0.x, c1.x, c2.x,
            c0.y, c1.y, c2.y,
            c0.z, c1.z, c2.z
        );
    }

    static constexpr Mat3 identity() noexcept {
        return Mat3(
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0
        );
    }

    static constexpr Mat3 zero() noexcept {
        return Mat3();
    }

    // Element access
    constexpr double operator()(std::size_t row, std::size_t col) const noexcept {
        return e[row][col];
    }

    constexpr double& operator()(std::size_t row, std::size_t col) noexcept {
        return e[row][col];
    }

    // Row & column getters
    constexpr Vec3 row(std::size_t r) const noexcept {
        return Vec3(e[r][0], e[r][1], e[r][2]);
    }

    constexpr Vec3 col(std::size_t c) const noexcept {
        return Vec3(e[0][c], e[1][c], e[2][c]);
    }

    // Arithmetic
    constexpr Mat3 operator+(const Mat3& other) const noexcept {
        Mat3 result;
        for (std::size_t r = 0; r < 3; ++r) {
            for (std::size_t c = 0; c < 3; ++c) {
                result.e[r][c] = e[r][c] + other.e[r][c];
            }
        }
        return result;
    }

    constexpr Mat3 operator-(const Mat3& other) const noexcept {
        Mat3 result;
        for (std::size_t r = 0; r < 3; ++r) {
            for (std::size_t c = 0; c < 3; ++c) {
                result.e[r][c] = e[r][c] - other.e[r][c];
            }
        }
        return result;
    }

    constexpr Mat3 operator*(double s) const noexcept {
        Mat3 result;
        for (std::size_t r = 0; r < 3; ++r) {
            for (std::size_t c = 0; c < 3; ++c) {
                result.e[r][c] = e[r][c] * s;
            }
        }
        return result;
    }

    // Matrix-matrix product
    constexpr Mat3 operator*(const Mat3& other) const noexcept {
        Mat3 result;
        for (std::size_t r = 0; r < 3; ++r) {
            for (std::size_t c = 0; c < 3; ++c) {
                result.e[r][c] = dot(row(r), other.col(c));
            }
        }
        return result;
    }

    // Matrix-vector product
    constexpr Vec3 operator*(const Vec3& v) const noexcept {
        return Vec3(
            dot(row(0), v),
            dot(row(1), v),
            dot(row(2), v)
        );
    }

    // Transpose
    constexpr Mat3 transpose() const noexcept {
        return Mat3(
            e[0][0], e[1][0], e[2][0],
            e[0][1], e[1][1], e[2][1],
            e[0][2], e[1][2], e[2][2]
        );
    }

    // Determinant
    constexpr double determinant() const noexcept {
        double c0 = e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1]);
        double c1 = e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0]);
        double c2 = e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
        return c0 - c1 + c2;
    }

    // Inverse - returns std::nullopt if matrix is singular
    constexpr std::optional<Mat3> inverse(double eps = kEpsilon) const noexcept {
        double det = determinant();
        if (std::abs(det) < eps) {
            return std::nullopt;
        }

        double inv_det = 1.0 / det;

        // Adjugate matrix entries
        double m00 =  (e[1][1] * e[2][2] - e[1][2] * e[2][1]);
        double m01 = -(e[0][1] * e[2][2] - e[0][2] * e[2][1]);
        double m02 =  (e[0][1] * e[1][2] - e[0][2] * e[1][1]);

        double m10 = -(e[1][0] * e[2][2] - e[1][2] * e[2][0]);
        double m11 =  (e[0][0] * e[2][2] - e[0][2] * e[2][0]);
        double m12 = -(e[0][0] * e[1][2] - e[0][2] * e[1][0]);

        double m20 =  (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
        double m21 = -(e[0][0] * e[2][1] - e[0][1] * e[2][0]);
        double m22 =  (e[0][0] * e[1][1] - e[0][1] * e[1][0]);

        return Mat3(
            m00 * inv_det, m01 * inv_det, m02 * inv_det,
            m10 * inv_det, m11 * inv_det, m12 * inv_det,
            m20 * inv_det, m21 * inv_det, m22 * inv_det
        );
    }

    // Rotation matrices around cardinal axes
    static Mat3 rotation_x(double phi) noexcept {
        double cos_p = std::cos(phi);
        double sin_p = std::sin(phi);
        return Mat3(
            1.0,   0.0,    0.0,
            0.0, cos_p, -sin_p,
            0.0, sin_p,  cos_p
        );
    }

    static Mat3 rotation_y(double phi) noexcept {
        double cos_p = std::cos(phi);
        double sin_p = std::sin(phi);
        return Mat3(
             cos_p, 0.0, sin_p,
               0.0, 1.0,   0.0,
            -sin_p, 0.0, cos_p
        );
    }

    static Mat3 rotation_z(double phi) noexcept {
        double cos_p = std::cos(phi);
        double sin_p = std::sin(phi);
        return Mat3(
            cos_p, -sin_p, 0.0,
            sin_p,  cos_p, 0.0,
              0.0,    0.0, 1.0
        );
    }
};

inline std::ostream& operator<<(std::ostream& out, const Mat3& m) {
    out << "\n[" << m(0,0) << ", " << m(0,1) << ", " << m(0,2) << "]\n"
        << "[" << m(1,0) << ", " << m(1,1) << ", " << m(1,2) << "]\n"
        << "[" << m(2,0) << ", " << m(2,1) << ", " << m(2,2) << "]\n";
    return out;
}

} // namespace lightrail
