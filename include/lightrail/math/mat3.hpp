#pragma once

#include <optional>
#include "lightrail/math/algebra_structures.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

class Quaternion;

/**
 * @brief 3x3 Matrix for 3D coordinate transformations, rotations, and Lie algebra representations.
 * Satisfies Group, Ring, VectorSpace, and NormedAlgebra.
 */
class Mat3 : public NormedAlgebraInterface<Mat3, double> {
public:
    double m[3][3]{{0.0}};

    // Constructors
    Mat3();
    explicit Mat3(double diag);
    Mat3(double m00, double m01, double m02,
         double m10, double m11, double m12,
         double m20, double m21, double m22);

    // Static factories
    static Mat3 identity();
    static Mat3 zero();
    static Mat3 rotation_x(double radians);
    static Mat3 rotation_y(double radians);
    static Mat3 rotation_z(double radians);
    static Mat3 from_quaternion(const Quaternion& q);

    // Row and column accessors
    Vec3 row(int r) const;
    Vec3 col(int c) const;

    // Linear algebra operations
    Mat3 transpose() const;
    double determinant() const;
    std::optional<Mat3> inverse() const;
    Quaternion to_quaternion() const;

    // Algebraic arithmetic
    Mat3 operator-() const;
    Mat3 operator+(const Mat3& other) const;
    Mat3 operator-(const Mat3& other) const;
    Mat3 operator*(const Mat3& other) const;
    Vec3 operator*(const Vec3& v) const;
    Mat3 operator*(double s) const;
    Mat3 operator/(double s) const;

    bool operator==(const Mat3& other) const;
    bool operator!=(const Mat3& other) const;

    friend double norm(const Mat3& mat);
};

// Scalar * Matrix
Mat3 operator*(double s, const Mat3& mat);

// Frobenius norm for 3x3 Matrix
double norm(const Mat3& mat);

} // namespace lightrail
