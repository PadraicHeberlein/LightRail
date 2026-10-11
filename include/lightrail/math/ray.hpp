#pragma once

#include <iostream>
#include "lightrail/math/vec3.hpp"

namespace lightrail {

struct Ray {
    Point3 origin;
    Vec3 direction;

    constexpr Ray() noexcept = default;
    constexpr Ray(const Point3& origin, const Vec3& direction) noexcept
        : origin(origin), direction(direction) {}

    // Evaluate parametric point along ray: P(t) = origin + t * direction
    constexpr Point3 at(double t) const noexcept {
        return origin + t * direction;
    }
};

inline std::ostream& operator<<(std::ostream& out, const Ray& r) {
    return out << "Ray(origin: " << r.origin << ", dir: " << r.direction << ')';
}

} // namespace lightrail
