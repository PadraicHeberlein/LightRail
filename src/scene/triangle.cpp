#include "lightrail/scene/triangle.hpp"
#include <cmath>
#include <stdexcept>

namespace lightrail {

Triangle::Triangle(const Point3& v0, const Point3& v1, const Point3& v2, std::shared_ptr<Material> mat)
    : v0(v0), v1(v1), v2(v2), normal(unit_vector(cross(v1 - v0, v2 - v0))), material(std::move(mat)) {}

bool Triangle::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
    // TODO: Implement Möller–Trumbore ray-triangle intersection algorithm
    // 1. edge1 = v1 - v0, edge2 = v2 - v0
    // 2. h = cross(r.direction, edge2)
    // 3. a = dot(edge1, h)
    // 4. If std::abs(a) < kEpsilon, ray is parallel to triangle, return false
    // 5. f = 1.0 / a
    // 6. s = r.origin - v0
    // 7. u = f * dot(s, h); if u < 0.0 || u > 1.0, return false
    // 8. q = cross(s, edge1)
    // 9. v = f * dot(r.direction, q); if v < 0.0 || (u + v) > 1.0, return false
    // 10. t = f * dot(edge2, q); if t < t_min || t > t_max, return false
    // 11. Populate rec: rec.t = t, rec.point = r.at(t), rec.set_face_normal, rec.material = material
    throw std::logic_error("Not implemented: Triangle::hit() (Möller–Trumbore)");
}

} // namespace lightrail
