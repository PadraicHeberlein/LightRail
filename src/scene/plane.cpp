#include "lightrail/scene/plane.hpp"
#include <cmath>
#include <stdexcept>

namespace lightrail {

Plane::Plane(const Point3& point, const Vec3& normal, std::shared_ptr<Material> mat)
    : point_on_plane(point), normal(unit_vector(normal)), material(std::move(mat)) {}

Plane::Plane(const Point3& p0, const Point3& p1, const Point3& p2, std::shared_ptr<Material> mat)
    : point_on_plane(p0), material(std::move(mat)) {
    // TODO: Calculate normal vector from cross product of edge vectors: (p0 - p1) x (p1 - p2)
    throw std::logic_error("Not implemented: Plane::Plane(p0, p1, p2)");
}

void Plane::enable_checkerboard(double scale, const Color& color2) {
    checkerboard = true;
    checker_scale = scale;
    checker_color2 = color2;
}

bool Plane::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // TODO: Implement analytical ray-plane intersection
    // 1. Compute denom = dot(normal, r.direction)
    // 2. If std::abs(denom) < kEpsilon, ray is parallel, return false
    // 3. Compute t = dot(point_on_plane - r.origin, normal) / denom
    // 4. Verify t lies within [t_min, t_max]
    // 5. Populate rec.t, rec.point = r.at(t), rec.set_face_normal
    // 6. If checkerboard is enabled, modulate diffuse albedo based on floor(x/scale) ^ floor(z/scale)
    throw std::logic_error("Not implemented: Plane::hit()");
}

} // namespace lightrail
