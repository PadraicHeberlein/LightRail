#include "lightrail/math/ray.hpp"
#include <stdexcept>

namespace lightrail {

Ray::Ray() : origin(Point3::zero()), direction(Vec3::unit_z()) {}

Ray::Ray(const Point3& origin, const Vec3& direction)
    : origin(origin), direction(direction) {}

Point3 Ray::at(double t) const {
    return origin + t * direction;
}

} // namespace lightrail
