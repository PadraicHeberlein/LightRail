#pragma once

#include "lightrail/math/vec3.hpp"

namespace lightrail {

/**
 * @brief Parametric 3D ray represented by origin O and direction vector D.
 * Point along ray at distance t is given by P(t) = O + t * D.
 */
struct Ray {
    Point3 origin;
    Vec3 direction;

    Ray();
    Ray(const Point3& origin, const Vec3& direction);

    /**
     * @brief Computes 3D point along ray at parameter t.
     * Formula: origin + t * direction
     */
    Point3 at(double t) const;
};

} // namespace lightrail
