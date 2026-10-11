#pragma once

#include <memory>
#include "lightrail/image/color.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

/**
 * @brief Infinite 3D Plane geometry.
 * Ported from undergrad PlaneR3.cs and LineR3.cs.
 * Equation: dot(P - P0, N) = 0
 */
class Plane : public Hittable {
public:
    Point3 point_on_plane;
    Vec3 normal;
    std::shared_ptr<Material> material;
    bool checkerboard{false};
    double checker_scale{1.0};
    Color checker_color2{0.2, 0.2, 0.2};

    // Point and normal constructor
    Plane(const Point3& point, const Vec3& normal, std::shared_ptr<Material> mat);

    // Three-point constructor: defines plane through non-collinear points p0, p1, p2
    Plane(const Point3& p0, const Point3& p1, const Point3& p2, std::shared_ptr<Material> mat);

    void enable_checkerboard(double scale = 1.0, const Color& color2 = Color(0.2, 0.2, 0.2));

    /**
     * @brief Tests ray intersection with plane.
     * Ray equation: P(t) = O + t*D
     * Intersects plane at: t = dot(P0 - O, N) / dot(D, N)
     */
    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

} // namespace lightrail
