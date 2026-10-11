#include "lightrail/scene/sphere.hpp"
#include <cmath>
#include <stdexcept>

namespace lightrail {

Sphere::Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat)
    : center(center), radius(radius), material(std::move(mat)) {}

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // TODO: Implement analytical quadratic ray-sphere intersection
    // 1. Compute oc = r.origin - center
    // 2. Compute a = r.direction.length_squared()
    // 3. Compute half_b = dot(oc, r.direction)
    // 4. Compute c = oc.length_squared() - radius * radius
    // 5. Compute discriminant = half_b * half_b - a * c
    // 6. If discriminant < 0, return false
    // 7. Find nearest root in [t_min, t_max]: (-half_b - sqrt(disc)) / a, or (+ root)
    // 8. Populate rec.t, rec.point = r.at(rec.t), rec.set_face_normal, rec.material = material
    throw std::logic_error("Not implemented: Sphere::hit()");
}

} // namespace lightrail
