#pragma once

#include <memory>
#include "lightrail/math/constants.hpp"
#include "lightrail/scene/hittable.hpp"

namespace lightrail {

// Infinite 3D Plane ported from undergrad PlaneR3.cs and LineR3.cs
class Plane : public Hittable {
public:
    Point3 point_on_plane;
    Vec3 normal;
    std::shared_ptr<Material> material;
    bool checkerboard{false};
    double checker_scale{1.0};
    Color checker_color2{0.2, 0.2, 0.2};

    Plane(const Point3& point, const Vec3& normal, std::shared_ptr<Material> mat)
        : point_on_plane(point), normal(unit_vector(normal)), material(std::move(mat)) {}

    // Ported from PlaneR3(PointR3 p0, PointR3 p1, PointR3 p2)
    Plane(const Point3& p0, const Point3& p1, const Point3& p2, std::shared_ptr<Material> mat)
        : point_on_plane(p0),
          normal(unit_vector(cross(p0 - p1, p1 - p2))),
          material(std::move(mat)) {}

    void enable_checkerboard(double scale = 1.0, const Color& color2 = Color(0.2, 0.2, 0.2)) noexcept {
        checkerboard = true;
        checker_scale = scale;
        checker_color2 = color2;
    }

    bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override {
        double denom = dot(normal, r.direction);

        // If denom is close to zero, ray is parallel to the plane
        if (std::abs(denom) < kEpsilon) {
            return false;
        }

        // Analytical line-plane intersection:
        // t = ( (P0 - Origin) . Normal ) / ( Direction . Normal )
        double t = dot(point_on_plane - r.origin, normal) / denom;

        if (t < t_min || t > t_max) {
            return false;
        }

        rec.t = t;
        rec.point = r.at(t);
        rec.set_face_normal(r, normal);

        if (checkerboard && material) {
            // Checkered texture by coordinates
            int cx = static_cast<int>(std::floor(rec.point.x / checker_scale));
            int cz = static_cast<int>(std::floor(rec.point.z / checker_scale));
            bool is_even = (cx + cz) % 2 == 0;

            // Make a local material copy with current tile color
            auto tile_mat = std::make_shared<Material>(*material);
            tile_mat->albedo = is_even ? material->albedo : checker_color2;
            rec.material = tile_mat;
        } else {
            rec.material = material;
        }

        return true;
    }
};

} // namespace lightrail
