/**
 * @file vec3.hpp
 * @brief 3D Euclidean vector (`Vec3` / `Point3`) arithmetic, vector products, optical reflection/refraction, and stochastic sampling.
 * @see [Ray Tracing in One Weekend: The vec3 Class](https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class)
 * @see [Euclidean Vector (Wikipedia)](https://en.wikipedia.org/wiki/Euclidean_vector)
 */
#pragma once

#include <iosfwd>
#include "lightrail/math/constants.hpp"

namespace lightrail {

/**
 * @brief 3D Vector representation @f$ \mathbf{v} = (x, y, z) \in \mathbb{R}^3 @f$ for geometric and physical calculations.
 * @see [Ray Tracing in One Weekend: The vec3 Class](https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class)
 * @see [PBRT v4: Vectors and Points](https://www.pbr-book.org/4ed/Geometry_and_Transformations/Vectors)
 */
struct Vec3 {
    double x{0.0};
    double y{0.0};
    double z{0.0};

    // Constructors
    constexpr Vec3() noexcept = default;
    constexpr Vec3(double x, double y, double z) noexcept : x(x), y(y), z(z) {}

    // Static factories
    static constexpr Vec3 zero() noexcept { return Vec3(0.0, 0.0, 0.0); }
    static constexpr Vec3 unit_x() noexcept { return Vec3(1.0, 0.0, 0.0); }
    static constexpr Vec3 unit_y() noexcept { return Vec3(0.0, 1.0, 0.0); }
    static constexpr Vec3 unit_z() noexcept { return Vec3(0.0, 0.0, 1.0); }

    /**
     * @brief Returns the Euclidean norm @f$ \|\mathbf{v}\| = \sqrt{x^2 + y^2 + z^2} @f$.
     */
    [[nodiscard]] double length() const;

    /**
     * @brief Returns the squared Euclidean norm @f$ \|\mathbf{v}\|^2 = x^2 + y^2 + z^2 @f$ (avoids `std::sqrt`).
     */
    [[nodiscard]] double length_squared() const;

    /**
     * @brief Checks component-wise approximate equality within @p epsilon.
     */
    [[nodiscard]] bool approx_equal(const Vec3& other, double epsilon = kEpsilon) const;

    constexpr bool operator==(const Vec3& other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    }

    // Compound assignment operators
    Vec3& operator+=(const Vec3& other);
    Vec3& operator-=(const Vec3& other);
    Vec3& operator*=(double s);
    Vec3& operator/=(double s);

    // Unary negation
    [[nodiscard]] Vec3 operator-() const;
};

/// @brief Semantic alias distinguishing 3D spatial positions from displacement directions.
using Point3 = Vec3;

// Vector arithmetic operators
[[nodiscard]] Vec3 operator+(const Vec3& a, const Vec3& b);
[[nodiscard]] Vec3 operator-(const Vec3& a, const Vec3& b);

/**
 * @brief Component-wise (Hadamard) product @f$ (a_x b_x, a_y b_y, a_z b_z) @f$.
 * @see [Hadamard Product (Wikipedia)](https://en.wikipedia.org/wiki/Hadamard_product_(matrices))
 */
[[nodiscard]] Vec3 operator*(const Vec3& a, const Vec3& b);
[[nodiscard]] Vec3 operator*(double s, const Vec3& v);
[[nodiscard]] Vec3 operator*(const Vec3& v, double s);
[[nodiscard]] Vec3 operator/(const Vec3& v, double s);

/**
 * @brief Computes the dot (scalar) product @f$ \mathbf{a} \cdot \mathbf{b} = a_x b_x + a_y b_y + a_z b_z @f$.
 * @see [Dot Product (Wikipedia)](https://en.wikipedia.org/wiki/Dot_product)
 */
[[nodiscard]] double dot(const Vec3& a, const Vec3& b);

/**
 * @brief Computes the right-handed cross product @f$ \mathbf{a} \times \mathbf{b} @f$.
 * @see [Cross Product (Wikipedia)](https://en.wikipedia.org/wiki/Cross_product)
 */
[[nodiscard]] Vec3 cross(const Vec3& a, const Vec3& b);

/**
 * @brief Returns the normalized unit vector @f$ \hat{\mathbf{v}} = \mathbf{v} / \|\mathbf{v}\| @f$.
 * @pre @p v must be non-zero.
 */
[[nodiscard]] Vec3 unit_vector(const Vec3& v);

[[nodiscard]] bool is_parallel(const Vec3& a, const Vec3& b);
[[nodiscard]] bool is_perpendicular(const Vec3& a, const Vec3& b);

/**
 * @brief Computes mirror reflection of vector @p v off a surface with unit @p normal.
 *
 * Formula: @f$ \mathbf{r} = \mathbf{v} - 2(\mathbf{v} \cdot \mathbf{n})\mathbf{n} @f$.
 *
 * @image html reflection_refraction.svg "Specular Reflection and Snell's Law Refraction"
 *
 * @param v Incident direction vector.
 * @param normal Unit surface normal.
 * @return Reflected direction vector.
 * @pre @p normal must be a unit vector.
 * @see [Ray Tracing in One Weekend: Mirrored Light Reflection](https://raytracing.github.io/books/RayTracingInOneWeekend.html#metal/mirroredlightreflection)
 * @see [Specular Reflection (Wikipedia)](https://en.wikipedia.org/wiki/Specular_reflection)
 */
[[nodiscard]] Vec3 reflect(const Vec3& v, const Vec3& normal);

/**
 * @brief Computes Snell's Law refraction of unit vector @p uv through a surface with unit normal @p n.
 *
 * Decomposes the refracted ray into perpendicular and parallel components:
 * @f$ \mathbf{r}_\perp = \frac{\eta_i}{\eta_t}(\mathbf{u}_v + \cos\theta\,\mathbf{n}) @f$,
 * @f$ \mathbf{r}_\parallel = -\sqrt{|1 - \|\mathbf{r}_\perp\|^2|}\,\mathbf{n} @f$.
 *
 * @param uv Unit incident ray direction.
 * @param n Unit surface normal pointing against @p uv.
 * @param etai_over_etat Ratio of refractive indices @f$ \eta_i / \eta_t @f$.
 * @return Refracted unit direction vector.
 * @pre @p uv and @p n must be unit vectors.
 * @see [Snell's Law (Wikipedia)](https://en.wikipedia.org/wiki/Snell%27s_law)
 * @see [Ray Tracing in One Weekend: Snell's Law](https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics/snellslaw)
 * @see [Scratchapixel: Reflection, Refraction and Fresnel](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel.html)
 */
[[nodiscard]] Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat);

/**
 * @brief Linear interpolation between two vectors: @f$ (1 - t)\mathbf{a} + t\mathbf{b} @f$.
 * @param a Start vector (@f$ t = 0 @f$).
 * @param b End vector (@f$ t = 1 @f$).
 * @param t Blend factor.
 * @return Interpolated vector.
 * @see [Linear Interpolation (Wikipedia)](https://en.wikipedia.org/wiki/Linear_interpolation)
 */
[[nodiscard]] Vec3 lerp(const Vec3& a, const Vec3& b, double t);

/**
 * @brief Uniformly samples a random point inside the unit sphere (@f$ \|\mathbf{p}\| < 1 @f$) via rejection sampling.
 * @see [Rejection Sampling (Wikipedia)](https://en.wikipedia.org/wiki/Rejection_sampling)
 * @see [Ray Tracing in One Weekend: Generating Random Vectors](https://raytracing.github.io/books/RayTracingInOneWeekend.html#diffusematerials/asimplediffusematerial)
 */
[[nodiscard]] Vec3 random_in_unit_sphere();

/**
 * @brief Uniformly samples a random unit vector on the surface of the unit sphere @f$ S^2 @f$.
 * @see [Sphere Point Picking (MathWorld)](https://mathworld.wolfram.com/SpherePointPicking.html)
 */
[[nodiscard]] Vec3 random_unit_vector();

/**
 * @brief Uniformly samples a random point inside the unit disk in the @f$ xy @f$-plane (used for thin-lens depth of field).
 * @see [Ray Tracing in One Weekend: Defocus Blur](https://raytracing.github.io/books/RayTracingInOneWeekend.html#defocusblur/generatingraysfromthedefocusdisk)
 */
[[nodiscard]] Vec3 random_in_unit_disk();

// Stream output
std::ostream& operator<<(std::ostream& os, const Vec3& v);

} // namespace lightrail
