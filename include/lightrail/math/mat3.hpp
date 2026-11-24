/**
 * @file mat3.hpp
 * @brief 3x3 real matrix class for 3D linear transformations, Euler rotations, and @f$ SO(3) @f$ / @f$ \mathfrak{so}(3) @f$ representations.
 * @see [Rotation Matrix (Wikipedia)](https://en.wikipedia.org/wiki/Rotation_matrix)
 * @see [Invertible Matrix & Adjugate Formula (Wikipedia)](https://en.wikipedia.org/wiki/Invertible_matrix)
 */
#pragma once

#include <optional>
#include "lightrail/math/algebra_structures.hpp"
#include "lightrail/math/vec3.hpp"

namespace lightrail {

class Quaternion;

/**
 * @brief 3x3 Matrix for 3D coordinate transformations, rotations, and Lie algebra representations.
 *
 * Satisfies Group, Ring, VectorSpace, and NormedAlgebra concepts.
 *
 * @see [Rotation Matrix (Wikipedia)](https://en.wikipedia.org/wiki/Rotation_matrix)
 * @see [3D Rotation Group SO(3) (Wikipedia)](https://en.wikipedia.org/wiki/3D_rotation_group)
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

    /**
     * @brief Constructs an elementary right-handed rotation matrix about the X axis by @p radians.
     * @see [Basic 3D Rotations (Wikipedia)](https://en.wikipedia.org/wiki/Rotation_matrix#Basic_3D_rotations)
     */
    static Mat3 rotation_x(double radians);

    /**
     * @brief Constructs an elementary right-handed rotation matrix about the Y axis by @p radians.
     */
    static Mat3 rotation_y(double radians);

    /**
     * @brief Constructs an elementary right-handed rotation matrix about the Z axis by @p radians.
     */
    static Mat3 rotation_z(double radians);

    /**
     * @brief Converts a unit Quaternion into its equivalent 3x3 @f$ SO(3) @f$ rotation matrix.
     * @see [Quaternion-Derived Rotation Matrix (Wikipedia)](https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix)
     */
    static Mat3 from_quaternion(const Quaternion& q);

    // Row and column accessors
    [[nodiscard]] Vec3 row(int r) const;
    [[nodiscard]] Vec3 col(int c) const;

    /**
     * @brief Returns the matrix transpose @f$ A^T @f$ (equals @f$ A^{-1} @f$ for orthogonal rotation matrices).
     * @see [Transpose (Wikipedia)](https://en.wikipedia.org/wiki/Transpose)
     */
    [[nodiscard]] Mat3 transpose() const;

    /**
     * @brief Computes the 3x3 determinant @f$ \det(A) @f$ via cofactor expansion / Rule of Sarrus.
     * @see [Determinant (Wikipedia)](https://en.wikipedia.org/wiki/Determinant)
     */
    [[nodiscard]] double determinant() const;

    /**
     * @brief Computes the matrix inverse @f$ A^{-1} = \frac{1}{\det(A)} \operatorname{adj}(A) @f$, or `std::nullopt` if singular.
     * @return Inverted Mat3 if @f$ |\det(A)| > \epsilon @f$, otherwise `std::nullopt`.
     * @see [Adjugate Matrix (Wikipedia)](https://en.wikipedia.org/wiki/Adjugate_matrix)
     */
    [[nodiscard]] std::optional<Mat3> inverse() const;

    /**
     * @brief Extracts the equivalent unit Quaternion from an @f$ SO(3) @f$ rotation matrix (Shepperd's method).
     * @see [Rotation Matrix to Quaternion (Wikipedia)](https://en.wikipedia.org/wiki/Rotation_matrix#Quaternion)
     */
    [[nodiscard]] Quaternion to_quaternion() const;

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

/**
 * @brief Computes the Frobenius norm @f$ \|A\|_F = \sqrt{\sum_{i,j} A_{ij}^2} @f$ of a 3x3 matrix.
 * @param mat Input matrix.
 * @return Non-negative Frobenius norm.
 * @see [Frobenius Norm (Wikipedia)](https://en.wikipedia.org/wiki/Matrix_norm#Frobenius_norm)
 */
double norm(const Mat3& mat);

} // namespace lightrail
