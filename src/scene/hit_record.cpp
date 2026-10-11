#include "lightrail/scene/hit_record.hpp"
#include <stdexcept>

namespace lightrail {

void HitRecord::set_face_normal(const Ray& r, const Vec3& outward_normal) {
    // TODO: Determine face orientation and set normal against ray direction
    // front_face = dot(r.direction, outward_normal) < 0.0;
    // normal = front_face ? outward_normal : -outward_normal;
    throw std::logic_error("Not implemented: HitRecord::set_face_normal()");
}

} // namespace lightrail
