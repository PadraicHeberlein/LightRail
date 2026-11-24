/**
 * @file ray.hpp
 * @brief Parametric 3D ray @f$ \mathbf{P}(t) = \mathbf{O} + t\mathbf{D} @f$ used across all geometric intersection tests.
 * @see [Ray Tracing in One Weekend: Rays, a Simple Camera, and Background](https://raytracing.github.io/books/RayTracingInOneWeekend.html#rays,asimplecamera,andbackground)
 * @see [PBRT v4: Rays](https://www.pbr-book.org/4ed/Geometry_and_Transformations/Rays)
 */
#pragma once

#include "lightrail/math/vec3.hpp"

namespace lightrail {

/**
 * @brief Parametric 3D ray represented by origin @f$ \mathbf{O} @f$ and direction vector @f$ \mathbf{D} @f$.
 *
 * A point along the ray at parameter @f$ t \in \mathbb{R} @f$ is evaluated as
 * @f$ \mathbf{P}(t) = \mathbf{O} + t\mathbf{D} @f$.
 *
 * @see [Ray Tracing in One Weekend: The Ray Class](https://raytracing.github.io/books/RayTracingInOneWeekend.html#rays,asimplecamera,andbackground/therayclass)
 * @see [PBRT v4: Rays](https://www.pbr-book.org/4ed/Geometry_and_Transformations/Rays)
 */
struct Ray {
    Point3 origin;
    Vec3 direction;

    Ray();
    Ray(const Point3& origin, const Vec3& direction);

    /**
     * @brief Computes the 3D point along the ray at parameter @p t: @f$ \mathbf{P}(t) = \mathbf{O} + t\mathbf{D} @f$.
     * @param t Parametric distance along `direction` (positive values lie in front of `origin`).
     * @return World-space 3D point @f$ \mathbf{P}(t) @f$.
     */
    [[nodiscard]] Point3 at(double t) const;
};

} // namespace lightrail
